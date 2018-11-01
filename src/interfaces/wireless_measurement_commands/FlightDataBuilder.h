#ifndef AHRS_FLIGHTDATABUILDER_H
#define AHRS_FLIGHTDATABUILDER_H

#include "MeasuringDataBuilder.h"

namespace communication
{
    class FlightDataBuilder final : public MeasuringDataBuilder
    {
    public:
        FlightDataBuilder();

        virtual std::unique_ptr<MeasuringData> create(const std::vector<uint8_t> &dataInBytes) override;

    };
}

#endif