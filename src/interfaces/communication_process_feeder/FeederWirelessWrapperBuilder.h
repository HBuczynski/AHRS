#ifndef FEEDERWIRELESSWRAPPERBUILDER_H
#define FEEDERWIRELESSWRAPPERBUILDER_H

#include "FeederCommandBuilder.h"

namespace communication
{
    class FeederWirelessWrapperBuilder final : public FeederCommandBuilder
    {
    public:
        FeederWirelessWrapperBuilder();
        ~FeederWirelessWrapperBuilder();

        std::unique_ptr<FeederCommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif // FEEDERWIRELESSWRAPPERBUILDER_H
