#include "../include/BITExecutor.h"

#include <iostream>
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
        bitsInformation_.m_communication = 25;
    else
        bitsInformation_.m_communication = 0;
}

void BITExecutor::checkIMU()
{
    bitsInformation_.m_imu = 25;
}

void BITExecutor::checkGPS()
{
    const auto status = gpsInterface_.getStatus();

    if(status == gps::GPSStatus::FIXED)
    {    
        bitsInformation_.m_gps = 25;
        cout << "FIXED GPS. " << endl;
    }
    else
        bitsInformation_.m_gps = 42;
}

const communication::BitsInformation& BITExecutor::getBitsInformation() const noexcept
{
    return bitsInformation_;
}

void BITExecutor::approveConnection() noexcept
{
    connectionBITS_ = true;
}

