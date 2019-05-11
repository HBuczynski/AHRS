#include "../include/IMUCalibrator.h"

#include <iostream>

using namespace std;
using namespace communication;

IMUCalibrator::IMUCalibrator()
    : accelInit_(false),
      magInit_(false),
      ellInit_(false),
      prevAxis_(-1),
      currentAxis_(-1),
      accelIsDone_(false),
      magIsDone_(false),
      ellIsDone_(false)
{
    currentAxis_ = 0;
    config_.status = CalibrationStatus::CALIB_IN_THE_PROCESS;
}

void IMUCalibrator::setFileName(const std::string& name)
{
    fileName_ = name;
}

bool IMUCalibrator::initializeCalibration()
{
    settings = new RTIMUSettings(fileName_.c_str());

    if (imu != NULL)
        delete imu;

    imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
        return false;

    imu->IMUInit();

    imu->setCompassCalibrationMode(true);
    imu->setAccelCalibrationMode(true);
    magCal = new RTIMUMagCal(settings);
    magCal->magCalInit();

    accelCal = new RTIMUAccelCal(settings);
    accelCal->accelCalInit();

    return true;
}

void IMUCalibrator::calibrateDevice()
{
    if(!accelIsDone_)
    {
        lock_guard<mutex> lock(mutex_);
        calibrateAccel();
    }
    else if (!magIsDone_)
    {
        lock_guard<mutex> lock(mutex_);
        calibrateMag();
    }
    else if (!ellIsDone_)
    {
        lock_guard<mutex> lock(mutex_);
        calibrateEll();
    }

    if(accelIsDone_ && magIsDone_ && ellIsDone_)
        config_.status = CalibrationStatus::IS_CALIBRATED;
}

void IMUCalibrator::calibrateAccel()
{
    if (!accelInit_)
    {
        for (int i = 0; i < 3; i++)
            accelCal->accelCalEnable(i, true);
        
        accelCal->accelCalReset();
  
        for (int i = 0; i < 3; i++)
            accelCal->accelCalEnable(i, false);

        for (int i = 0; i < 3; i++)
            axes[i].first = axes[i].second = false;

        accelInit_ = true;
    }

    usleep(imu->IMUGetPollInterval() * 1000);


    for (int i = 0; i < 3; i++)
        accelCal->accelCalEnable(i, axes[i].first);
    accelCal->newAccelCalData(imuData.accel);

    config_.accelerometer.axis = currentAxis_;
    config_.accelerometer.mode = axes[currentAxis_].first ? 1 : 0;
    config_.accelerometer.approved = axes[currentAxis_].second ? 1 : 0;


    config_.accelerometer.maxX = accelCal->m_accelMax.data(0);
    config_.accelerometer.minX = accelCal->m_accelMin.data(0);

    config_.accelerometer.maxY = accelCal->m_accelMax.data(1);
    config_.accelerometer.minY = accelCal->m_accelMin.data(1);

    config_.accelerometer.maxZ = accelCal->m_accelMax.data(2);
    config_.accelerometer.minZ = accelCal->m_accelMin.data(2);

    if(axes[0].second && axes[1].second && axes[2].second)
    {
        accelIsDone_ = true;
        config_.progress |= 0x01;
    }
}

void IMUCalibrator::calibrateAccelX()
{
    config_.accelerometer.maxX += 0.01;
    config_.accelerometer.minX -= 0.01;
}

void IMUCalibrator::calibrateAccelY()
{
    config_.accelerometer.maxY += 0.01;
    config_.accelerometer.minY -= 0.01;
}

void IMUCalibrator::calibrateAccelZ()
{
    config_.accelerometer.maxZ += 0.01;
    config_.accelerometer.minZ -= 0.01;
}

void IMUCalibrator::calibrateMag()
{
    lock_guard<mutex> lock(mutex_);
    if (!magInit_)
    {
        magCal->magCalInit();
        magInit_ = true;
    }

    usleep(imu->IMUGetPollInterval() * 1000);

    while (pollIMU()) 
        magCal->newMinMaxData(imuData.compass);

    config_.magnetometer.maxX = magCal->m_magMax.data(0);
    config_.magnetometer.maxY = magCal->m_magMax.data(1);
    config_.magnetometer.maxZ = magCal->m_magMax.data(2);

    config_.magnetometer.minX = magCal->m_magMin.data(0);
    config_.magnetometer.minY = magCal->m_magMin.data(1);
    config_.magnetometer.minZ = magCal->m_magMin.data(2);

}

void IMUCalibrator::calibrateEll()
{
    config_.ellipsoid.quadrant_11 += 1;
    config_.ellipsoid.quadrant_12 += 1;
    config_.ellipsoid.quadrant_13 += 4;
    config_.ellipsoid.quadrant_21 += 3;
    config_.ellipsoid.quadrant_22 += 2;
    config_.ellipsoid.quadrant_23 += 1;
    config_.ellipsoid.quadrant_31 += 1;
    config_.ellipsoid.quadrant_32 += 2;
    config_.ellipsoid.quadrant_33 += 5;

    checkEllCondition();
}

void IMUCalibrator::checkEllCondition()
{
    bool condition = ( config_.ellipsoid.quadrant_11 > 200 ) &&
                     ( config_.ellipsoid.quadrant_12 > 200 ) &&
                     ( config_.ellipsoid.quadrant_13 > 200 ) &&
                     ( config_.ellipsoid.quadrant_21 > 200 ) &&
                     ( config_.ellipsoid.quadrant_22 > 200 ) &&
                     ( config_.ellipsoid.quadrant_23 > 200 ) &&
                     ( config_.ellipsoid.quadrant_31 > 200 ) &&
                     ( config_.ellipsoid.quadrant_32 > 200 ) &&
                     ( config_.ellipsoid.quadrant_33 > 200 );

    if (condition)
    {
        config_.ellipsoid.mode = 1;
        config_.progress |= 0x04;
        ellIsDone_ = true;
    }
}

void IMUCalibrator::enableAccelAxis(uint8_t axis)
{
    lock_guard<mutex> lock(mutex_);
    axes[currentAxis_].first = true;
}

void IMUCalibrator::disableAccelAxis(uint8_t axis)
{
    lock_guard<mutex> lock(mutex_);
    axes[currentAxis_].first = false;
}

void IMUCalibrator::nextAccelAxis()
{
    lock_guard<mutex> lock(mutex_);

    prevAxis_ = currentAxis_;
    if(prevAxis_)
        axes[prevAxis_].first = false;

    ++currentAxis_;
    if( currentAxis_ >= 3)
        currentAxis_ = 0;
}

void IMUCalibrator::approveAccelAxis(uint8_t axis)
{
    lock_guard<mutex> lock(mutex_);
    axes[axis].second = true;
    accelCal->accelCalSave();
}

void IMUCalibrator::approveMagnetometer()
{
    lock_guard<mutex> lock(mutex_);
    magCal->magCalSaveMinMax();
    magIsDone_ = true;
    config_.progress |= 0x02;
}

const CalibrationConfiguration& IMUCalibrator::getConfiguration()
{
    return config_;
}

bool IMUCalibrator::pollIMU()
{
    if (imu->IMURead()) {
        imuData = imu->getIMUData();
        return true;
    } else {
        return false;
    }
}

