#include "PlaneOrientation.h"
#include "../../3rd_party/RTIMULib/RTIMULib.h"
#include "../../3rd_party/RTIMULib/RTMath.h"

#include <iostream>
#include <unistd.h>

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
//    delete imu;
//    delete settings;
}

void PlaneOrientation::initDataAcquisition()
{
//    settings = new RTIMUSettings("RTIMULib");
//    imu = RTIMU::createIMU(settings);
//
//    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
//        printf("No IMU found\n");
//        exit(1);
//    }

    //  This is an opportunity to manually override any settings before the call IMUInit

    //  set up IMU
//    imu->IMUInit();
//
//    //  this is a convenient place to change fusion parameters
//
//    imu->setSlerpPower(0.02);
//    imu->setGyroEnable(true);
//    imu->setAccelEnable(true);
//    imu->setCompassEnable(true);

    //  set up for rate timer


}

void PlaneOrientation::readData()
{

    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    RTIMU *imu = RTIMU::createIMU(settings);

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

    //  now just process data

    while (1) {
        //  poll at the rate recommended by the IMU

        usleep(imu->IMUGetPollInterval() * 1000);

        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
            sampleCount++;

            now_ = RTMath::currentUSecsSinceEpoch();

            //  display 10 times per second

            if ((now_ - displayTimer) > 100000) {
                printf("Sample rate %d: %s\r", sampleRate, RTMath::displayDegrees("", imuData.fusionPose));
                fflush(stdout);
                displayTimer = now_;
            }

            //  update rate every second

            if ((now_ - rateTimer) > 1000000) {
                sampleRate = sampleCount;
                sampleCount = 0;
                rateTimer = now_;
            }
        }
    }
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

