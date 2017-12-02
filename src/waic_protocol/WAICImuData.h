#ifndef AHRS_BLACK_BOX_WAICIMUDATA_H
#define AHRS_BLACK_BOX_WAICIMUDATA_H

#include "WAICMeasuringData.h"

namespace communication
{
    class WAICImuData final : public WAICMeasuringData
    {
    public:
        WAICImuData();
        WAICImuData(const std::vector<uint8_t>& frameBytes);
        ~WAICImuData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

    private:

    };
}

#endif