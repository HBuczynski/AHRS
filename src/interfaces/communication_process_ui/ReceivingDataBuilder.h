#ifndef AHRS_RECEIVINGDATABUILDER_H
#define AHRS_RECEIVINGDATABUILDER_H

#include <UINotificationBuilder.h>

namespace communication
{
    class ReceivingDataBuilder final : public UINotificationBuilder
    {
    public:
        ReceivingDataBuilder();
        ~ReceivingDataBuilder();

        std::unique_ptr<UINotification> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif