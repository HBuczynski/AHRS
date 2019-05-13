#ifndef UDPBITSNOTIFBUILDER_H
#define UDPBITSNOTIFBUILDER_H

#include "FeederNotificationBuilder.h"

namespace communication
{
    class UDPBitsNotifBuilder final : public FeederNotificationBuilder
    {
    public:
        UDPBitsNotifBuilder();
        ~UDPBitsNotifBuilder();

        virtual std::unique_ptr<FeederNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // UDPBITSNOTIFBUILDER_H
