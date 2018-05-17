#ifndef AHRS_BLACK_BOX_MEASURINGDATA_H
#define AHRS_BLACK_BOX_MEASURINGDATA_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class MeasuringDataVisitor;

    enum MeasuringType : uint8_t
    {
        IMU = 10,
        GPS = 20
    };

    class MeasuringData : public Frame
    {
    public:
        MeasuringData(uint8_t dataSizeIn, MeasuringType responseTypeIn);
        virtual ~MeasuringData();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(MeasuringDataVisitor& visitor) = 0;

        const MeasuringType& getMeasuringType() const;

    protected:
        virtual void initializeDataSize() = 0;

        MeasuringType measuringType_;
    };
}

#endif
