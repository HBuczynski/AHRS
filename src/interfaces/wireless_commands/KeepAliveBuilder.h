#ifndef KEEPALIVEBUILDER_H
#define KEEPALIVEBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class KeepAliveBuilder final : public CommandBuilder
    {
    public:
        KeepAliveBuilder();
        ~KeepAliveBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // KEEPALIVEBUILDER_H
