#ifndef BITEXECUTOR_H
#define BITEXECUTOR_H

#include <interfaces/wireless_responses/BITsResponse.h>
#include "GPSAdafruitInterface.h"

#include <atomic>
#include <thread>

class BITExecutor
{
public:
    BITExecutor();

    void checkConnection();
    void checkIMU();
    void checkGPS();

    void approveConnection() noexcept;

    const communication::BitsInformation& getBitsInformation() noexcept;

private:
    std::atomic<bool> connectionBITS_;

    communication::BitsInformation bitsInformation_;
    gps::GPSAdafruitInterface gpsInterface_;
};

#endif // BITEXECUTOR_H
