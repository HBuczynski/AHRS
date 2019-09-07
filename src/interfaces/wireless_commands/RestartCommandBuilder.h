#ifndef RESTARTCOMMANDBUILDER_H
#define RESTARTCOMMANDBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class RestartCommandBuilder final : public CommandBuilder
    {
    public:
        RestartCommandBuilder();
        ~RestartCommandBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // RESTARTCOMMANDBUILDER_H
