#ifndef AHRS_IMUGPSBUILDER_H
#define AHRS_IMUGPSBUILDER_H

#include "MeasuringDataBuilder.h"

namespace communication
{
    class GpsDataBuilder final : public MeasuringDataBuilder
    {
    public:
        GpsDataBuilder();

        virtual std::unique_ptr<MeasuringData> create(const std::vector<uint8_t> &dataInBytes) override;

    };
}

#endif
