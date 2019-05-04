#include "../include/IMUCalibrator.h"

#include <iostream>

using namespace std;
using namespace communication;

IMUCalibrator::IMUCalibrator()
    : prevAxis_(-1),
      currentAxis_(-1),
      accelIsDone_(false),
      magIsDone_(false),
      ellIsDone_(false)
{
    currentAxis_ = 0;
    config_.status = CalibrationStatus::CALIB_IN_THE_PROCESS;
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
    if (currentAxis_ == 0 && axes[currentAxis_].first)
        calibrateAccelX();
    else if (currentAxis_ == 1 && axes[currentAxis_].first)
        calibrateAccelY();
    else if (currentAxis_ == 2 && axes[currentAxis_].first)
        calibrateAccelZ();

    config_.accelerometer.axis = currentAxis_;
    config_.accelerometer.mode = axes[currentAxis_].first ? 1 : 0;
    config_.accelerometer.approved = axes[currentAxis_].second ? 1 : 0;

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
    config_.magnetometer.maxX += 0.02;
    config_.magnetometer.maxY += 0.06;
    config_.magnetometer.maxZ += 0.027;

    config_.magnetometer.minX -= 0.0356;
    config_.magnetometer.minY -= 0.4356;
    config_.magnetometer.minZ -= 0.2356;
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
}

void IMUCalibrator::approveMagnetometer()
{
    lock_guard<mutex> lock(mutex_);
    magIsDone_ = true;
    config_.progress |= 0x02;
}

const CalibrationConfiguration& IMUCalibrator::getConfiguration()
{
    return config_;
}
