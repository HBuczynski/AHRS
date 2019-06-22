#ifndef AHRS_COMMUNICATIONSTATUSNOTIFICATION_H
#define AHRS_COMMUNICATIONSTATUSNOTIFICATION_H

#include "UINotification.h"
#include "../../common/UIStates.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class CommunicationStatusNotification : public UINotification
    {
    public:
        CommunicationStatusNotification(const UIExternalComCode &state, config::UICommunicationMode mode);
        ~CommunicationStatusNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UINotificationVisitor& visitor) override;

        UIExternalComCode getState() const;
        void setState(UIExternalComCode mode);

        config::UICommunicationMode getUIMode() const;
        void setUIMode(config::UICommunicationMode mode);

    private:
        virtual void initializeDataSize() override;

        UIExternalComCode state_;
        config::UICommunicationMode mode_;
    };
}

#endif
