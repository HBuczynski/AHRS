#include "../include/BITExecutor.h"

using namespace communication;

BITExecutor::BITExecutor()
{}

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

const communication::BitsInformation& BITExecutor::getBitsInformation() noexcept
{
    return bitsInformation_;
}
