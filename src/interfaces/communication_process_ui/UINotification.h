#ifndef AHRS_UINOTIFICATION_H
#define AHRS_UINOTIFICATION_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class UINotificationVisitor;

    enum UINotificationType : uint8_t
    {
        COMMMUNICATION_PROCESS_STATUS = 0x01,
        RECEIVING_DATA = 0x02,
        DATABASE_NAME = 0x03
    };

    class UINotification : public Frame
    {
    public:
        UINotification(uint8_t dataSizeIn, UINotificationType commandTypeIn);
        virtual ~UINotification();

        virtual std::vector<uint8_t > getFrameBytes() = 0;
        virtual std::string getName() = 0;
        virtual void accept(UINotificationVisitor& visitor) = 0;

        const UINotificationType& getCommandType() const;

    protected:
        virtual void initializeDataSize() = 0;

        UINotificationType uiNotificationType;
    };
}

#endif
