#ifndef BITSDATABUILDER_H
#define BITSDATABUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class BITSDataBuilder final : public CommandBuilder
    {
    public:
        BITSDataBuilder();
        ~BITSDataBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif // BITSDATABUILDER_H
