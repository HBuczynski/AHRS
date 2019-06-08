#ifndef HMCOMMANDFACTORY_H
#define HMCOMMANDFACTORY_H

#include "HMCommand.h"
#include "HMCommandBuilder.h"

#include <memory>

namespace communication
{
    class HMCommandFactory
    {
    public:
        HMCommandFactory();
        ~HMCommandFactory();

        std::unique_ptr<HMCommand> createCommand(const std::vector<uint8_t> &notificationInBytes);

    private:
        std::unique_ptr<HMCommandBuilder> builder_;

    };
}

#endif // HMCOMMANDFACTORY_H
