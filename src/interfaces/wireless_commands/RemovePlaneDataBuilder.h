#ifndef AHRS_REMOVEPLANEDATABUILDER_H
#define AHRS_REMOVEPLANEDATABUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class RemovePlaneDataBuilder final : public CommandBuilder
    {
    public:
        RemovePlaneDataBuilder();
        ~RemovePlaneDataBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif
