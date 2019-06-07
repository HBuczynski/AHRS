#ifndef HMREGISTERMAINBUILDER_H
#define HMREGISTERMAINBUILDER_H

#include "HMNotificationBuilder.h"

namespace communication
{
    class HMRegisterMainBuilder final : public HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // HMREGISTERMAINBUILDER_H
