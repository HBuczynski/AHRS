#ifndef AHRS_RECONNECTBUILDER_H
#define AHRS_RECONNECTBUILDER_H

#include "UICommandBuilder.h"

namespace communication
{
    class ReconnectBuilder final : public UICommandBuilder
    {
    public:
        ReconnectBuilder();
        ~ReconnectBuilder();

        std::unique_ptr<UICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif