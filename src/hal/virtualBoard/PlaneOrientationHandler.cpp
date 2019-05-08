#include "../include/PlaneOrientationHandler.h"

#include <time_manager/TimeManager.h>
#include <config_reader/FeederParameters.h>
#include <RTIMULib.h>
#include <iostream>

using namespace std;
using namespace utility;
using namespace telemetry;

PlaneOrientationHandler::PlaneOrientationHandler()
    : counter_(0),
      logger_(Logger::getInstance())
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
    return true;
}

void PlaneOrientationHandler::readData()
{
    ++counter_;
}

const IMUData& PlaneOrientationHandler::getImuData() noexcept
{
    imuData_.pitch = 180.0f * sin( counter_ / 9000.0f );
    imuData_.roll = 90.0f * sin( counter_ /  20000.0f );
    imuData_.yaw = 360.0f * sin( counter_ /  4000.0f );

    imuData_.accelX = sin(counter_/234.0f);
    imuData_.accelY = sin(counter_/233234.0f);
    imuData_.accelZ = sin(counter_/9804.0f);

    imuData_.timestamp = utility::TimeManager::getImeSinceEpoch();

    return imuData_;
}
