#ifndef AHRS_STARTACQUISITIONBUILDER_H
#define AHRS_STARTACQUISITIONBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class StartAcquisitionBuilder final : public CommandBuilder
    {
    public:
        StartAcquisitionBuilder();
        ~StartAcquisitionBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}


#endif