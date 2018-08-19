#ifndef AHRS_UINOTIFICATIONFACTORY_H
#define AHRS_UINOTIFICATIONFACTORY_H

#include "UINotification.h"
#include "UINotificationBuilder.h"

namespace communication
{
    class UINotificationFactory
    {
    public:
        UINotificationFactory();
        ~UINotificationFactory();

        std::unique_ptr<UINotification> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<UINotificationBuilder> builder_;
    };
}


#endif