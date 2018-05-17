#ifndef AHRS_FEEDERCOMMANDBUILDER_H
#define AHRS_FEEDERCOMMANDBUILDER_H

#include "FeederCommand.h"

#include <memory>
#include <vector>

namespace communication
{
    class UICommandBuilder
    {
    public:
        virtual std::unique_ptr<FeederCommand> create(const std::vector<uint8_t> &commandInBytes) = 0;

    protected:
        const uint8_t initialDataPosition = 7;
    };
}

#endif //AHRS_FEEDERCOMMANDBUILDER_H
