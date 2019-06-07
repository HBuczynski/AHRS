#ifndef HMREGISTERBUILDER_H
#define HMREGISTERBUILDER_H

#include "HMNotificationBuilder.h"

namespace communication
{
    class HMRegisterBuilder final : public HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // HMREGISTERBUILDER_H
