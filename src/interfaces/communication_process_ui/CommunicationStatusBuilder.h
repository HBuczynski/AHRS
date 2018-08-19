#ifndef AHRS_COMMUNICATIONSTATUSBUILDER_H
#define AHRS_COMMUNICATIONSTATUSBUILDER_H

#include <UINotificationBuilder.h>

namespace communication
{
    class CommunicationStatusBuilder final : public UINotificationBuilder
    {
    public:
        CommunicationStatusBuilder();
        ~CommunicationStatusBuilder();

        std::unique_ptr<UINotification> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}


#endif