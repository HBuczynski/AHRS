#ifndef FMRESETCOMMUNICATIONPROCESSBUILDER_H
#define FMRESETCOMMUNICATIONPROCESSBUILDER_H

#include "FMCommandBuilder.h"

namespace communication
{
    class FMResetCommunicationProcessBuilder final : public FMCommandBuilder
    {
    public:
        virtual std::unique_ptr<FMCommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // FMRESETCOMMUNICATIONPROCESSBUILDER_H
