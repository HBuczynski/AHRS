#ifndef ETHFEEDERCOMMANDBUILDER_H
#define ETHFEEDERCOMMANDBUILDER_H

#include "EthFeederCommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class EthFeederCommandBuilder
    {
    public:
        virtual std::unique_ptr<EthFeederCommand> create(const std::vector<uint8_t> &commandInBytes) = 0;
    };
}

#endif // ETHFEEDERCOMMANDBUILDER_H
