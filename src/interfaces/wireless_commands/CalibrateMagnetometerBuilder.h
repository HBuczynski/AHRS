#ifndef AHRS_CALIBRATEMAGNETOMETERBUILDER_H
#define AHRS_CALIBRATEMAGNETOMETERBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CalibrateMagnetometerBuilder final : public CommandBuilder
    {
    public:
        CalibrateMagnetometerBuilder();
        ~CalibrateMagnetometerBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
        
    };
}

#endif