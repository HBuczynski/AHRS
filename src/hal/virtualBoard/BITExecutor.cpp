#include "../include/BITExecutor.h"
#include <iostream>

#include <config_reader/ConfigurationReader.h>
#include <config_reader/FeederParameters.h>

using namespace std;
using namespace config;
using namespace communication;

BITExecutor::BITExecutor()
    : connectionBITS_(false),
      gpsInterface_(FEEDER_GPS_DEVICE_FILE)
{
    gpsInterface_.initialize();
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

const communication::BitsInformation& BITExecutor::getBitsInformation() noexcept
{
    FeederMode mode = ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH).mode;
    bitsInformation_.mode = static_cast<int>(mode);

    cout << "\nMode: " << to_string(static_cast<int>(mode)) << endl;

    return bitsInformation_;
}

void BITExecutor::approveConnection() noexcept
{
    connectionBITS_ = true;
}
