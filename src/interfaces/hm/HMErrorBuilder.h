#ifndef AHRS_ERRORBUILDER_H
#define AHRS_ERRORBUILDER_H

#include "HMNotificationBuilder.h"

namespace communication
{
    class HMErrorBuilder final : public HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}


#endif
