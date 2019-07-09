#ifndef FMCOMMANDFACTORY_H
#define FMCOMMANDFACTORY_H

#include "FMCommand.h"
#include "FMCommandBuilder.h"

#include <memory>

namespace communication
{
    class FMCommandFactory
    {
    public:
        FMCommandFactory();
        ~FMCommandFactory();

        std::unique_ptr<FMCommand> createCommand(const std::vector<uint8_t> &notificationInBytes);

    private:
        std::unique_ptr<FMCommandBuilder> builder_;

    };
}
#endif // FMCOMMANDFACTORY_H
