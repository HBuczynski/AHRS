#include "PlaneOrientation.h"
#include "../../3rd_party/RTIMULib/RTIMULib.h"

#include <iostream>

using namespace std;
using namespace utility;
using namespace telemetry;

PlaneOrientation::PlaneOrientation()
    : logger_(Logger::getInstance())
{
    int sampleCount = 0;
    int sampleRate = 0;

}

PlaneOrientation::~PlaneOrientation()
{
    delete imu;
    delete settings;
}

void PlaneOrientation::initDataAcquisition()
{
    settings = new RTIMUSettings("RTIMULib");
    imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

    //  This is an opportunity to manually override any settings before the call IMUInit

    //  set up IMU

    imu->IMUInit();

    //  this is a convenient place to change fusion parameters

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    //  set up for rate timer

    rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();
}

void PlaneOrientation::readData()
{
    usleep(imu->IMUGetPollInterval() * 1000);

    while (imu->IMURead()) {
        imuData = imu->getIMUData();

        now_ = RTMath::currentUSecsSinceEpoch();
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

