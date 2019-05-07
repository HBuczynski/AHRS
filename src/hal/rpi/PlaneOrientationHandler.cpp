#include "PlaneOrientationHandler.h"

#include <config_reader/FeederParameters.h>
#include <RTIMULib.h>
#include <iostream>

using namespace std;
using namespace utility;
using namespace telemetry;

PlaneOrientationHandler::PlaneOrientationHandler()
    : logger_(Logger::getInstance())
{}

PlaneOrientationHandler::~PlaneOrientationHandler()
{
    if(settings_)
        delete settings_;

    if(imu_)
        delete imu_;
}

bool PlaneOrientationHandler::initDataAcquisition(const std::string& planeName)
{
    const auto filePath = config::FEEDER_AIRCRAFTS_DATABASE_PATH + planeName;

    settings_ = new RTIMUSettings(filePath.c_str());
    imu_ = RTIMU::createIMU(settings_);

    if ((imu_ == NULL) || (imu_->IMUType() == RTIMU_TYPE_NULL))
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("PlaneOrientation :: Cannot initialize IMU.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return false;
    }
    imu_->IMUInit();

    imu_->setSlerpPower(0.02);
    imu_->setGyroEnable(true);
    imu_->setAccelEnable(true);
    imu_->setCompassEnable(true);

    return true;
}

void PlaneOrientationHandler::readData()
{
    usleep(imu_->IMUGetPollInterval() * 1000);

    while (imu_->IMURead())
    {
        imuData_ = imu_->getIMUData();
    }
}

const IMUData& PlaneOrientationHandler::getImuData() const noexcept
{
    imuData_.pitch = rtImuData_.fusionPose.y()*RTMATH_RAD_TO_DEGREE;
    imuData_.roll = rtImuData_.fusionPose.x()*RTMATH_RAD_TO_DEGREE;
    imuData_.yaw = rtImuData_.fusionPose.z()*RTMATH_RAD_TO_DEGREE;

    imuData_.accelX = rtImuData_.accel.x();
    imuData_.accelY = rtImuData_.accel.y();
    imuData_.accelZ = rtImuData_.accel.z();

    imuData_.timestamp = 0; //TODO

    return imuData_;
}

