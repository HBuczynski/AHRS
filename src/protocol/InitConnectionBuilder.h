#ifndef AHRS_BLACK_BOX_INITCONNECTIONBUILDER_H
#define AHRS_BLACK_BOX_INITCONNECTIONBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class InitConnectionBuilder final : public CommandBuilder
    {
    public:
        InitConnectionBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    private:
        const uint16_t INIT_PORT_POSITION_IN_FRAME = 7;
        const uint16_t INIT_ADDRESS_POSITION_IN_FRAME = 9;
    };
}
#endif
