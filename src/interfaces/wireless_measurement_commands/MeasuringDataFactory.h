#ifndef AHRS_MEASURINGDATAFACTORY_H
#define AHRS_MEASURINGDATAFACTORY_H

#include "MeasuringDataBuilder.h"

namespace communication
{
    class MeasuringDataFactory
    {
    public:
        MeasuringDataFactory();
        ~MeasuringDataFactory();
        std::unique_ptr<MeasuringData> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<MeasuringDataBuilder> builder_;

    };
}

#endif