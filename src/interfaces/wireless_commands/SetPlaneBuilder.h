#ifndef AHRS_SETPLANEBUILDER_H
#define AHRS_SETPLANEBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class SetPlaneBuilder final : public CommandBuilder
    {
    public:
        SetPlaneBuilder();
        ~SetPlaneBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif
