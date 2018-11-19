#include "PlaneOrientation.h"
#include "../../3rd_party/RTIMULib/RTIMULibDefs.h"

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
{}

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
    RTIMU_DATA imuData = imu->getIMUData();
}

float PlaneOrientation::getPitch()
{
    return imuData.fusionPose.x();
}

float PlaneOrientation::getRoll()
{
    return imuData.fusionPose.y();
}

float PlaneOrientation::getYaw()
{
    return imuData.fusionPose.z();
}

