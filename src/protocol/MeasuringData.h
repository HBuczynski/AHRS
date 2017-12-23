#ifndef AHRS_BLACK_BOX_WAICMEASURINGDATA_H
#define AHRS_BLACK_BOX_WAICMEASURINGDATA_H

#include "Frame.h"

namespace communication
{
    enum MeasuringType : uint8_t
    {
        IMU,
        GPS
    };

    class MeasuringData : public Frame
    {
    public:
        MeasuringData(uint8_t dataSizeIn, MeasuringType responseTypeIn);
        virtual ~MeasuringData();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;

        const MeasuringType& getMeasuringType();

    protected:
        MeasuringType measuringType;
    };
}

#endif
