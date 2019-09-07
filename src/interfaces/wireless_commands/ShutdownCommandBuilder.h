#ifndef SHUTDOWNCOMMANDBUILDER_H
#define SHUTDOWNCOMMANDBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class ShutdownCommandBuilder final : public CommandBuilder
    {
    public:
        ShutdownCommandBuilder();
        ~ShutdownCommandBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // SHUTDOWNCOMMANDBUILDER_H
