#ifndef AHRS_BLACK_BOX_WAICIMUDATA_H
#define AHRS_BLACK_BOX_WAICIMUDATA_H

#include "MeasuringData.h"

namespace communication
{
    class ImuData final : public MeasuringData
    {
    public:
        ImuData();
        ImuData(const std::vector<uint8_t>& frameBytes);
        ~ImuData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

    private:

    };
}

#endif