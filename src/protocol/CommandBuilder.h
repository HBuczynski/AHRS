#ifndef AHRS_BLACK_BOX_COMMANDBUILDER_H
#define AHRS_BLACK_BOX_COMMANDBUILDER_H

#include "Command.h"

#include <memory>
#include <vector>

namespace communication
{
    class CommandBuilder
    {
    public:
        CommandBuilder();
        virtual ~CommandBuilder();

        virtual std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes);
    };
}

#endif
