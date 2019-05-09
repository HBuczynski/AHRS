#ifndef SETHASHBUILDER_H
#define SETHASHBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class SetHashBuilder final : public CommandBuilder
    {
    public:
        SetHashBuilder();
        ~SetHashBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif // SETHASHBUILDER_H
