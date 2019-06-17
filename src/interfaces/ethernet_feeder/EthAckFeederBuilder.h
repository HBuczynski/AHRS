#ifndef ETHACKFEEDERBUILDER_H
#define ETHACKFEEDERBUILDER_H

#include "EthFeederResponseBuilder.h"

namespace communication
{
    class EthAckFeederBuilder final : public EthFeederResponseBuilder
    {
    public:
        std::unique_ptr<EthFeederResponse> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // ETHACKFEEDERBUILDER_H
