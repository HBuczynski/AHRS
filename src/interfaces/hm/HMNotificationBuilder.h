#ifndef AHRS_FEEDERNOTIFICATIONBUILDER_H
#define AHRS_FEEDERNOTIFICATIONBUILDER_H

#include "HMNotification.h"

#include <memory>
#include <vector>

namespace communication
{
    class HMNotificationBuilder
    {
    public:
        virtual std::unique_ptr<HMNotification> create(const std::vector<uint8_t> &NotificationInBytes) = 0;
    };
}

#endif
