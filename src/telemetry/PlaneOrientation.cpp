#include "PlaneOrientation.h"

#include <RTIMULib.h>
#include <iostream>

using namespace std;
using namespace utility;
using namespace telemetry;

PlaneOrientation::PlaneOrientation()
    : logger_(Logger::getInstance())
{
    settings = new RTIMUSettings("RTIMULib");
    imu = RTIMU::createIMU(settings);
}

PlaneOrientation::~PlaneOrientation()
{
    delete imu;
    delete settings;
}

bool PlaneOrientation::initDataAcquisition()
{
    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL))
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("PlaneOrientation :: Cannot initialize IMU.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return false;
    }
    imu->IMUInit();

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    return true;
}

void PlaneOrientation::readData()
{
    usleep(imu->IMUGetPollInterval() * 1000);

    while (imu->IMURead())
    {
        imuData = imu->getIMUData();
    }
}

float PlaneOrientation::getPitch()
{
    return imuData.fusionPose.y()*RTMATH_RAD_TO_DEGREE;
}

float PlaneOrientation::getRoll()
{
    return imuData.fusionPose.x()*RTMATH_RAD_TO_DEGREE;
}

float PlaneOrientation::getYaw()
{
    return imuData.fusionPose.z()*RTMATH_RAD_TO_DEGREE;
}

