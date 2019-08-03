#ifndef EthKeepAliveBuilder_H
#define EthKeepAliveBuilder_H

#include "EthFeederCommandBuilder.h"

namespace communication
{
    class EthKeepAliveBuilder final : public EthFeederCommandBuilder
    {
    public:
        EthKeepAliveBuilder();
        ~EthKeepAliveBuilder();

        std::unique_ptr<EthFeederCommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // EthKeepAliveBuilder_H
