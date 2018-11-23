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

    m_gravity.setScalar(0);
    m_gravity.setX(0);
    m_gravity.setY(0);
    m_gravity.setZ(1);
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

    prevX = 0;
    prevY = 0;
    prevZ = 0;

    return true;
}

void PlaneOrientation::readData()
{
    usleep(imu->IMUGetPollInterval() * 1000);

    while (imu->IMURead())
    {
        imuData = imu->getIMUData();

        fusedConjugate = imuData.fusionQPose.conjugate();

        // now do the rotation - takes two steps with qTemp as the intermediate variable

        qTemp = m_gravity * imuData.fusionQPose;
        rotatedGravity = fusedConjugate * qTemp;

        residuals.setX((rotatedGravity.x()));
        residuals.setY((rotatedGravity.y()));
        residuals.setZ((rotatedGravity.z()));

    }
}

float PlaneOrientation::getPitch()
{
    prevY = prevY *0.8 + residuals.y()*0.2*RTMATH_RAD_TO_DEGREE;
    return prevY;
}

float PlaneOrientation::getRoll()
{
    prevX = prevX *0.8 + residuals.x()*0.2*RTMATH_RAD_TO_DEGREE;
    return prevX;
}

float PlaneOrientation::getYaw()
{
    prevZ = prevZ *0.8 + residuals.z()*0.2*RTMATH_RAD_TO_DEGREE;
    return prevZ;
}

