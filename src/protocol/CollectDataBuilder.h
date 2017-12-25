#ifndef AHRS_COLLECTDATABUILDER_H
#define AHRS_COLLECTDATABUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CollectDataBuilder final : public CommandBuilder
    {
    public:
        CollectDataBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}
#endif
