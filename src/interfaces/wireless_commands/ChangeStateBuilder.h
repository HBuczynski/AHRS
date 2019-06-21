#ifndef CHANGESTATEBUILDER_H
#define CHANGESTATEBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class ChangeStateBuilder final : public CommandBuilder
    {
    public:
        ChangeStateBuilder();
        ~ChangeStateBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif // CHANGESTATEBUILDER_H
