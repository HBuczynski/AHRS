#include "../include/BITExecutor.h"

#include <config_reader/FeederParameters.h>

using namespace config;
using namespace communication;

BITExecutor::BITExecutor()
    :   gpsInterface_(FEEDER_GPS_DEVICE_FILE)
{
    gpsInterface_.initialize();
}

void BITExecutor::checkConnection()
{
    bitsInformation_.m_communication = 25;
    bitsInformation_.progress = 1;
}

void BITExecutor::checkIMU()
{
    bitsInformation_.m_imu = 25;
}

void BITExecutor::checkGPS()
{
    bitsInformation_.m_gps = 25;
}

const communication::BitsInformation& BITExecutor::getBitsInformation() const noexcept
{
    return bitsInformation_;
}
