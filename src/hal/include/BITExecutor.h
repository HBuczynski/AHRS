#ifndef BITEXECUTOR_H
#define BITEXECUTOR_H

#include <interfaces/wireless_responses/BITsResponse.h>
#include "GPSAdafruitInterface.h"

#include <thread>

class BITExecutor
{
public:
    BITExecutor();

    void checkConnection();
    void checkIMU();
    void checkGPS();

    const communication::BitsInformation& getBitsInformation() const noexcept;

private:
    communication::BitsInformation bitsInformation_;
    gps::GPSAdafruitInterface gpsInterface_;
};

#endif // BITEXECUTOR_H
