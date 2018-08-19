#ifndef AHRS_UINOTIFICATIONBUILDER_H
#define AHRS_UINOTIFICATIONBUILDER_H

#include "UINotification.h"

#include <memory>
#include <vector>

namespace communication
{
    class UINotificationBuilder
    {
    public:
        virtual std::unique_ptr<UINotification> create(const std::vector<uint8_t> &commandInBytes) = 0;
    };
}

#endif