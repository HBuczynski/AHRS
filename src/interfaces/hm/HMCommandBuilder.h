#ifndef HMCOMMANDBUILDER_H
#define HMCOMMANDBUILDER_H

#include "HMCommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class HMCommandBuilder
    {
    public:
        virtual std::unique_ptr<HMCommand> create(const std::vector<uint8_t> &NotificationInBytes) = 0;
    };
}

#endif // HMCOMMANDBUILDER_H
