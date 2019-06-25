#include "../include/BITExecutor.h"

#include <config_reader/ConfigurationReader.h>
#include <config_reader/FeederParameters.h>

using namespace config;
using namespace communication;

BITExecutor::BITExecutor()
    : connectionBITS_(false),
      gpsInterface_(FEEDER_GPS_DEVICE_FILE)
{
    gpsInterface_.initialize();
    bitsInformation_.mode = static_cast<int>(ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH).mode);
}

void BITExecutor::checkConnection()
{
    if(connectionBITS_)
        bitsInformation_.communication = 25;
    else
        bitsInformation_.communication = 0;
}

void BITExecutor::checkIMU()
{
    bitsInformation_.imu = 25;
}

void BITExecutor::checkGPS()
{
    bitsInformation_.gps = 25;
}

const communication::BitsInformation& BITExecutor::getBitsInformation() const noexcept
{
    return bitsInformation_;
}

void BITExecutor::approveConnection() noexcept
{
    connectionBITS_ = true;
}
