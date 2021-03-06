#ifndef AHRS_FEEDERCOMMANDBUILDER_H
#define AHRS_FEEDERCOMMANDBUILDER_H

#include "FeederCommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class FeederCommandBuilder
    {
    public:
        virtual std::unique_ptr<FeederCommand> create(const std::vector<uint8_t> &commandInBytes) = 0;

    };
}

#endif //AHRS_FEEDERCOMMANDBUILDER_H
