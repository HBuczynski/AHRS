#ifndef AHRS_BLACK_BOX_WAICMEASURINGDATA_H
#define AHRS_BLACK_BOX_WAICMEASURINGDATA_H

#include "WAICFrame.h"

namespace communication
{
    enum WAICMeasuringType : uint8_t
    {
        IMU,
        GPS
    };

    class WAICMeasuringData : public WAICFrame
    {
    public:
        WAICMeasuringData(uint8_t dataSizeIn, WAICMeasuringType responseTypeIn);
        virtual ~WAICMeasuringData();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        const WAICMeasuringType& getMeasuringType();

    protected:
        WAICMeasuringType measuringType;
    };
}

#endif
