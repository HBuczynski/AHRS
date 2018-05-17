#ifndef AHRS_FEEDERCOMMANDFACTORY_H
#define AHRS_FEEDERCOMMANDFACTORY_H

#include "FeederCommand.h"
#include "FeederCommandBuilder.h"

#include <memory>

namespace communication
{
    class FeederCommandFactory
    {
    public:
        FeederCommandFactory();
        ~FeederCommandFactory();

        std::unique_ptr<FeederCommand> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<UICommandBuilder> builder_;

        const uint8_t COMMAND_TYPE_POSITION = 5;
    };
}

#endif //AHRS_FEEDERCOMMANDFACTORY_H
