#ifndef HANDSHAKEBUILDER_H
#define HANDSHAKEBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class HandshakeBuilder final : public CommandBuilder
    {
    public:
        HandshakeBuilder();
        ~HandshakeBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // HANDSHAKEBUILDER_H
