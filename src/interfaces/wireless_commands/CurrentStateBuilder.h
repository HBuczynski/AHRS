#ifndef AHRS_CURRENTSTATEBUILDER_H
#define AHRS_CURRENTSTATEBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CurrentStateBuilder final : public CommandBuilder
    {
    public:
        CurrentStateBuilder();
        ~CurrentStateBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}
#endif