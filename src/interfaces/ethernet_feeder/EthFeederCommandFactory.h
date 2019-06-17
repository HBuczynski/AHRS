#ifndef ETHFEEDERCOMMANDFACTORY_H
#define ETHFEEDERCOMMANDFACTORY_H

#include "EthFeederCommand.h"
#include "EthFeederCommandBuilder.h"

#include <memory>

namespace communication
{
    class EthFeederCommandFactory
    {
    public:
        EthFeederCommandFactory();
        ~EthFeederCommandFactory();

        std::unique_ptr<EthFeederCommand> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<EthFeederCommandBuilder> builder_;
    };
}


#endif // ETHFEEDERCOMMANDFACTORY_H
