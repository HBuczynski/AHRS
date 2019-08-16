#ifndef HMINVALIDCONNECTIONBUILDER_H
#define HMINVALIDCONNECTIONBUILDER_H

#include "HMNotificationBuilder.h"

namespace communication
{
    class HMInvalidConnectionBuilder final : public HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif // HMINVALIDCONNECTIONBUILDER_H
