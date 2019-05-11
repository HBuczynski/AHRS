#include "../include/IMUCalibrator.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#define ELLIPSOID_FIT_DIR   "../../3rd_party/RTEllipsoidFit/"

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

IMUCalibrator::~IMUCalibrator()
{
    if (imu != NULL)
        delete imu;

    if (magCal != NULL)
        delete magCal;

    if (accelCal != NULL)
        delete accelCal;
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

    while (pollIMU()) 
    {
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
}

void IMUCalibrator::calibrateAccelX()
{}

void IMUCalibrator::calibrateAccelY()
{}

void IMUCalibrator::calibrateAccelZ()
{}

void IMUCalibrator::calibrateMag()
{
    if (!magInit_)
    {
        magCal->magCalInit();
        magInit_ = true;
    }

    usleep(imu->IMUGetPollInterval() * 1000);

    while (pollIMU()) 
    { 
        magCal->newMinMaxData(imuData.compass);

        config_.magnetometer.maxX = magCal->m_magMax.data(0);
        config_.magnetometer.maxY = magCal->m_magMax.data(1);
        config_.magnetometer.maxZ = magCal->m_magMax.data(2);

        config_.magnetometer.minX = magCal->m_magMin.data(0);
        config_.magnetometer.minY = magCal->m_magMin.data(1);
        config_.magnetometer.minZ = magCal->m_magMin.data(2);
    }
}

void IMUCalibrator::calibrateEll()
{
    usleep(imu->IMUGetPollInterval() * 1000);

    while (pollIMU()) {
        magCal->newEllipsoidData(imuData.compass);

        if (magCal->magCalEllipsoidValid()) 
        {
            magCal->magCalSaveRaw(ELLIPSOID_FIT_DIR);
            processEllipsoid();
    
            config_.ellipsoid.mode = 1;
            config_.progress |= 0x04;
            ellIsDone_ = true;
            
            return;
        }

        int counts[RTIMUCALDEFS_OCTANT_COUNT];
        magCal->magCalOctantCounts(counts);

        config_.ellipsoid.quadrant_11 = counts[0];
        config_.ellipsoid.quadrant_12 = counts[1];
        config_.ellipsoid.quadrant_13 = counts[2];
        config_.ellipsoid.quadrant_21 = counts[3];
        config_.ellipsoid.quadrant_22 = counts[4];
        config_.ellipsoid.quadrant_23 = counts[5];
        config_.ellipsoid.quadrant_31 = counts[6];
        config_.ellipsoid.quadrant_32 = counts[7];
    }
}

void IMUCalibrator::processEllipsoid()
{
    pid_t pid;
    int status;

    printf("\n\nProcessing ellipsoid fit data...\n");

    pid = fork();
    if (pid == 0) {
        //  child process
        chdir(ELLIPSOID_FIT_DIR);
        execl("/bin/sh", "/bin/sh", "-c", RTIMUCALDEFS_OCTAVE_COMMAND, NULL);
        printf("here");
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        printf("\nFailed to start ellipsoid fitting code.\n");
        return;
    } else {
        //  parent process - wait for child
        if (waitpid(pid, &status, 0) != pid) {
            printf("\n\nEllipsoid fit failed, %d\n", status);
        } else {
            if (status == 0) {
                printf("\nEllipsoid fit completed - saving data to file.");
                magCal->magCalSaveCorr(ELLIPSOID_FIT_DIR);
            } else {
                printf("\nEllipsoid fit returned %d - aborting.\n", status);
            }
        }
    }
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

