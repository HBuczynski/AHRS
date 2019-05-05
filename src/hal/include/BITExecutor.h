#ifndef BITEXECUTOR_H
#define BITEXECUTOR_H

#include <interfaces/wireless_responses/BITsResponse.h>

class BITExecutor
{
public:
    BITExecutor();

    void checkConnection();
    void checkIMU();
    void checkGPS();

    const communication::BitsInformation& getBitsInformation() noexcept;

private:
    communication::BitsInformation bitsInformation_;
};

#endif // BITEXECUTOR_H
