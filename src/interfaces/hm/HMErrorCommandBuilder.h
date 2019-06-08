#ifndef HMERRORCOMMANDBUILDER_H
#define HMERRORCOMMANDBUILDER_H

#include "HMCommandBuilder.h"

namespace communication
{
    class HMErrorCommandBuilder final : public HMCommandBuilder
    {
    public:
        virtual std::unique_ptr<HMCommand> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif // HMERRORCOMMANDBUILDER_H
