#ifndef HMREMOVENODEBUILDER_H
#define HMREMOVENODEBUILDER_H

#include "HMNotificationBuilder.h"

namespace communication
{
    class HMRemoveNodeBuilder final : public HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // HMREMOVENODEBUILDER_H
