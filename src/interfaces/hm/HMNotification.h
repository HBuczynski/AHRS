#ifndef AHRS_HMNotification_H
#define AHRS_HMNotification_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class HMNotificationVisitor;

    enum HMNotificationType : uint8_t
    {
        REGISTER = 0x05,
        HEARTBEAT = 0x10,
        MAIN_REGISTER = 0x15,
        ERROR = 0x20
    };

    class HMNotification : public Frame
    {
    public:
        HMNotification(uint8_t dataSizeIn, HMNotificationType notificationTypeIn);
        virtual ~HMNotification();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(HMNotificationVisitor& visitor) = 0;

        const HMNotificationType& getNotificationType() const;

    protected:
        virtual void initializeDataSize() = 0;

        HMNotificationType notificationType_;

    };
}

#endif
