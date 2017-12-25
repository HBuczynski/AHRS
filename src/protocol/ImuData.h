#ifndef AHRS_BLACK_BOX_WAICIMUDATA_H
#define AHRS_BLACK_BOX_WAICIMUDATA_H

#include "MeasuringData.h"

namespace communication
{
    class ImuData final : public MeasuringData
    {
    public:
        ImuData();
        ~ImuData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(MeasuringDataVisitor& visitor) override;

    private:
        virtual void initializeDataSize() override;
    };
}

#endif