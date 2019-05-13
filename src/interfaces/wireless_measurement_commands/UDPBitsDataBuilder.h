#ifndef UDPBITSBUILDER_H
#define UDPBITSBUILDER_H

#include "MeasuringDataBuilder.h"

namespace communication
{
    class UDPBitsDataBuilder final : public MeasuringDataBuilder
    {
    public:
        UDPBitsDataBuilder();

        virtual std::unique_ptr<MeasuringData> create(const std::vector<uint8_t> &dataInBytes) override;

    };
}

#endif // UDPBITSBUILDER_H
