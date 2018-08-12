#ifndef AHRS_FEEDERNOTIFICATIONFACTORY_H
#define AHRS_FEEDERNOTIFICATIONFACTORY_H

#include "FeederNotification.h"
#include "FeederNotificationBuilder.h"

#include <memory>

namespace communication
{
    class FeederNotificationFactory
    {
    public:
        FeederNotificationFactory();
        ~FeederNotificationFactory();

        std::unique_ptr<FeederNotification> createNotification(const std::vector<uint8_t> &notificationInBytes);

    private:
        std::unique_ptr<FeederNotificationBuilder> builder_;

    };
}


#endif
