#ifndef AHRS_HMNOTIFICATIONFACTORY_H
#define AHRS_HMNOTIFICATIONFACTORY_H

#include "HMNotification.h"
#include "HMNotificationBuilder.h"

#include <memory>

namespace communication
{
    class HMNotificationFactory
    {
    public:
        HMNotificationFactory();
        ~HMNotificationFactory();

        std::unique_ptr<HMNotification> createNotification(const std::vector<uint8_t> &notificationInBytes);

    private:
        std::unique_ptr<HMNotificationBuilder> builder_;

    };
}


#endif
