#ifndef AHRS_MEASURINGDATABUILDER_H
#define AHRS_MEASURINGDATABUILDER_H

#include "MeasuringData.h"
#include <memory>

namespace communication
{
    class MeasuringDataBuilder
    {
    public:
        virtual std::unique_ptr<MeasuringData> create(const std::vector<uint8_t> &dataInBytes) = 0;

    protected:
        const uint8_t initialDataPosition = 7;
    };
}

#endif
