#ifndef AHRS_HEARTBEATBUILDER_H
#define AHRS_HEARTBEATBUILDER_H

#include "HMNotificationBuilder.h"

namespace communication
{
    class HMHeartbeatBuilder final : public HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif
