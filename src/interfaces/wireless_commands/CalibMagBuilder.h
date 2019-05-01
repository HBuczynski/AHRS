#ifndef CALIBMAGBUILDER_H
#define CALIBMAGBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class CalibMagBuilder final : public CommandBuilder
    {
    public:
        CalibMagBuilder();
        ~CalibMagBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif // CALIBRATEACCELEROMETERBUILDER_H
