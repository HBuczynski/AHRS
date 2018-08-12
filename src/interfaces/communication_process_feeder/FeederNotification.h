#ifndef AHRS_FEEDERNOTIFICATION_H
#define AHRS_FEEDERNOTIFICATION_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class FeederNotificationVisitor;

    enum FeederNotificationType : uint8_t
    {
        CALIBRATION_STATUS_NOTIFY = 0x05
    };

    class FeederNotification : public Frame
    {
    public:
        FeederNotification(uint8_t dataSizeIn, FeederNotificationType NotificationTypeIn);
        virtual ~FeederNotification();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(FeederNotificationVisitor& visitor) = 0;

        const FeederNotificationType& getNotificationType() const;

    protected:
        virtual void initializeDataSize() = 0;

        FeederNotificationType notificationType_;

    };
}

#endif