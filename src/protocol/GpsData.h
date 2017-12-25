#ifndef AHRS_GPSDATA_H
#define AHRS_GPSDATA_H

#include "MeasuringData.h"

namespace communication
{
    class GpsData final : public MeasuringData
    {
    public:
        GpsData();
        ~GpsData();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;

    };
}

#endif //AHRS_GPSDATA_H
