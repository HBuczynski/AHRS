#ifndef DATABASENAMENOTIFICATION_H
#define DATABASENAMENOTIFICATION_H

#include "UINotification.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class DatabaseNameNotification : public UINotification
    {
    public:
        DatabaseNameNotification(config::UICommunicationMode mode);
        ~DatabaseNameNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UINotificationVisitor& visitor) override;

        void setMode(config::UICommunicationMode mode);
        config::UICommunicationMode getMode() const noexcept;

    private:
        virtual void initializeDataSize() override;

        config::UICommunicationMode mode_;
    };
}

#endif // DATABASENAMENOTIFICATION_H
