#ifndef HMRESTARTCHANGEMASTERBUILDER_H
#define HMRESTARTCHANGEMASTERBUILDER_H

#include "FMCommandBuilder.h"

namespace communication
{
    class FMRestartChangeMasterBuilder final : public FMCommandBuilder
    {
    public:
        virtual std::unique_ptr<FMCommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // HMRESTARTCHANGEMASTERBUILDER_H
