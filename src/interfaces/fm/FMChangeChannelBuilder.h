#ifndef FMCHANGECHANNELBUILDER_H
#define FMCHANGECHANNELBUILDER_H

#include "FMCommandBuilder.h"

namespace communication
{
    class FMChangeChannelBuilder final : public FMCommandBuilder
    {
    public:
        virtual std::unique_ptr<FMCommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // FMCHANGECHANNELBUILDER_H
