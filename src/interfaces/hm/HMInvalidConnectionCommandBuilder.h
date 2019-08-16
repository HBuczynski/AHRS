#ifndef HMINVALIDCONNECTIONCOMMANDBUILDER_H
#define HMINVALIDCONNECTIONCOMMANDBUILDER_H

#include "HMCommandBuilder.h"

namespace communication
{
    class HMInvalidConnectionCommandBuilder final : public HMCommandBuilder
    {
    public:
        virtual std::unique_ptr<HMCommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // HMINVALIDCONNECTIONCOMMANDBUILDER_H
