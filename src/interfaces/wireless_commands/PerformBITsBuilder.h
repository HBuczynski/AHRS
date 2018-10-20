#ifndef AHRS_PERFORMBITSBUILDER_H
#define AHRS_PERFORMBITSBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class PerformBITsBuilder final : public CommandBuilder
    {
    public:
        PerformBITsBuilder();
        ~PerformBITsBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif
