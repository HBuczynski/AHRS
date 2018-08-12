#ifndef AHRS_BLACK_BOX_COMMANDFACTORY_H
#define AHRS_BLACK_BOX_COMMANDFACTORY_H

#include "Command.h"
#include "CommandBuilder.h"

#include <memory>

namespace communication
{
    class CommandFactory
    {
    public:
        CommandFactory();
        ~CommandFactory();

        std::unique_ptr<Command> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<CommandBuilder> builder_;
    };
}
#endif
