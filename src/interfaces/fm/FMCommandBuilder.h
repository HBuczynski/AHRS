#ifndef FMCOMMANDBUILDER_H
#define FMCOMMANDBUILDER_H

#include "FMCommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class FMCommandBuilder
    {
    public:
        virtual std::unique_ptr<FMCommand> create(const std::vector<uint8_t> &commandInBytes) = 0;
    };
}

#endif // FMCOMMANDBUILDER_H
