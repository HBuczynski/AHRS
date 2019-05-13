#ifndef UDPBITSBUILDER_H
#define UDPBITSBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class UDPBitsBuilder final : public CommandBuilder
    {
    public:
        UDPBitsBuilder();
        ~UDPBitsBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif // UDPBITSBUILDER_H
