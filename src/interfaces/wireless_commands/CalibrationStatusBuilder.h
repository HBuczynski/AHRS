#ifndef AHRS_CALIBRATIONSTATUSBUILDER_H
#define AHRS_CALIBRATIONSTATUSBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CalibrationStatusBuilder final : public CommandBuilder
    {
    public:
        CalibrationStatusBuilder();
        ~CalibrationStatusBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}
#endif