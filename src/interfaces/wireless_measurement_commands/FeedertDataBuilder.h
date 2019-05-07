#ifndef AHRS_FLIGHTDATABUILDER_H
#define AHRS_FLIGHTDATABUILDER_H

#include "MeasuringDataBuilder.h"

namespace communication
{
    class FeedertDataBuilder final : public MeasuringDataBuilder
    {
    public:
        FeedertDataBuilder();

        virtual std::unique_ptr<MeasuringData> create(const std::vector<uint8_t> &dataInBytes) override;

    };
}

#endif
