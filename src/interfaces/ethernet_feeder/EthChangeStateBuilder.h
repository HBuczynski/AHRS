#ifndef ETHCHANGESTATEBUILDER_H
#define ETHCHANGESTATEBUILDER_H

#include "EthFeederCommandBuilder.h"

namespace communication
{
    class EthChangeStateBuilder final : public EthFeederCommandBuilder
    {
    public:
        std::unique_ptr<EthFeederCommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // ETHCHANGESTATEBUILDER_H
