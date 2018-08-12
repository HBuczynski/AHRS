#ifndef AHRS_IMUDATABUILDER_H
#define AHRS_IMUDATABUILDER_H

#include "MeasuringDataBuilder.h"

namespace communication
{
    class ImuDataBuilder final : public MeasuringDataBuilder
    {
    public:
        ImuDataBuilder();

        virtual std::unique_ptr<MeasuringData> create(const std::vector<uint8_t> &dataInBytes) override;

    };
}

#endif
