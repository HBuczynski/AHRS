#ifndef AHRS_SENDINGDATABUILDER_H
#define AHRS_SENDINGDATABUILDER_H

#include "UICommandBuilder.h"

namespace communication
{
    class SendingDataBuilder final : public UICommandBuilder
    {
    public:
        SendingDataBuilder();
        ~SendingDataBuilder();

        std::unique_ptr<UICommand> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif