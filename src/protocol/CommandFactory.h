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

        std::shared_ptr<Command> createCommand(std::vector<uint8_t> commandInBytes); // const ref, zmienic na unique

    private:
        std::unique_ptr<CommandBuilder> builder_;
    };
}
#endif
