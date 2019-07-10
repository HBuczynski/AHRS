#ifndef CHANGEFEEDERMODEBUILDER_H
#define CHANGEFEEDERMODEBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class ChangeFeederModeBuilder final : public CommandBuilder
    {
    public:
        ChangeFeederModeBuilder();
        ~ChangeFeederModeBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}


#endif // CHANGEFEEDERMODEBUILDER_H
