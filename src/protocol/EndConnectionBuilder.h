#ifndef AHRS_ENDCONNECTIONBUILDER_H
#define AHRS_ENDCONNECTIONBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class EndConnectionBuilder final : public CommandBuilder
    {
    public:
        EndConnectionBuilder();

        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif //AHRS_ENDCONNECTIONBUILDER_H
