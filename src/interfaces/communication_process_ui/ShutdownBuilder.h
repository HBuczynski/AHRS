#ifndef AHRS_SHUTDOWNBUILDER_H
#define AHRS_SHUTDOWNBUILDER_H

#include "UICommandBuilder.h"

namespace communication
{
    class ShutdownBuilder final : public UICommandBuilder
    {
    public:
        ShutdownBuilder();
        ~ShutdownBuilder();

        std::unique_ptr<UICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif