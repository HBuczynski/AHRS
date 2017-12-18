#ifndef AHRS_BLACK_BOX_INITCONNECTIONBUILDER_H
#define AHRS_BLACK_BOX_INITCONNECTIONBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class InitConnectionBuilder final : public CommandBuilder
    {
    public:
        InitConnectionBuilder();

        std::shared_ptr<Command> create(std::vector<uint8_t> commandInBytes) override;
    };
}
#endif
