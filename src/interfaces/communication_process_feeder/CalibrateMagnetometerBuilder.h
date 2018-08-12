#ifndef AHRS_CALIBRATEMAGNETOMETERBUILDER_H
#define AHRS_CALIBRATEMAGNETOMETERBUILDER_H

#include "FeederCommandBuilder.h"

namespace communication
{
    class CalibrateMagnetometerBuilder final : public FeederCommandBuilder
    {
    public:
        CalibrateMagnetometerBuilder();
        ~CalibrateMagnetometerBuilder();

        std::unique_ptr<FeederCommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}
#endif