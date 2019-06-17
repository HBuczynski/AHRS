#ifndef ETHINITCONNECTIONBUILDER_H
#define ETHINITCONNECTIONBUILDER_H

#include "EthFeederCommandBuilder.h"

namespace communication
{
    class EthInitConnectionBuilder final : public EthFeederCommandBuilder
    {
    public:
        std::unique_ptr<EthFeederCommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // ETHINITCONNECTIONBUILDER_H
