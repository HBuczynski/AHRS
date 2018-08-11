#ifndef AHRS_FEEDERNOTIFICATIONBUILDER_H
#define AHRS_FEEDERNOTIFICATIONBUILDER_H

#include "FeederNotification.h"

#include <memory>
#include <vector>

namespace communication
{
    class FeederNotificationBuilder
    {
    public:
        virtual std::unique_ptr<FeederNotification> create(const std::vector<uint8_t> &NotificationInBytes) = 0;

    protected:
        const uint8_t initialDataPosition = 7;
    };
}

#endif