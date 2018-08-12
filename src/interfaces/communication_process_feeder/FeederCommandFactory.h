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
        std::unique_ptr<FeederCommandBuilder> builder_;
    };
}

#endif //AHRS_FEEDERCOMMANDFACTORY_H
