#ifndef CALIBRATEACCELEROMETERBUILDER_H
#define CALIBRATEACCELEROMETERBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CalibrateAccelerometerBuilder final : public CommandBuilder
    {
    public:
        CalibrateAccelerometerBuilder();
        ~CalibrateAccelerometerBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif // CALIBRATEACCELEROMETERBUILDER_H
