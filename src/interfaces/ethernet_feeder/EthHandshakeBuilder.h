#ifndef ETHHANDSHAKEBUILDER_H
#define ETHHANDSHAKEBUILDER_H

#include "EthFeederCommandBuilder.h"

namespace communication
{
    class EthHandshakeBuilder final : public EthFeederCommandBuilder
    {
    public:
        std::unique_ptr<EthFeederCommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // ETHHANDSHAKEBUILDER_H
