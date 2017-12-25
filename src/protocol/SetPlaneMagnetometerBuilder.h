#ifndef AHRS_SETPLANEMAGNETOMETERBUILDER_H
#define AHRS_SETPLANEMAGNETOMETERBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class SetPlaneMagnetometerBuilder final : public CommandBuilder
    {
    public:
        SetPlaneMagnetometerBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif //AHRS_SETPLANEMAGNETOMETERBUILDER_H
