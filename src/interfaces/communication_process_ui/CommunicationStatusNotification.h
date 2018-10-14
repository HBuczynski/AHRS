#ifndef AHRS_COMMUNICATIONSTATUSNOTIFICATION_H
#define AHRS_COMMUNICATIONSTATUSNOTIFICATION_H

#include "UINotification.h"
#include "../../system_states/UIExternalComStates.h"

namespace communication
{
    class CommunicationStatusNotification : public UINotification
    {
    public:
        CommunicationStatusNotification(const UIExternalStateCode &state, uint8_t processNumber);
        ~CommunicationStatusNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UINotificationVisitor& visitor) override;

        UIExternalStateCode getState() const;
        void setState(UIExternalStateCode mode);

        uint8_t getProcessNumber() const;
        void setProcessNumber(uint8_t processNumber);

    private:
        virtual void initializeDataSize() override;

        UIExternalStateCode state_;
        uint8_t processNumber_;
    };
}

#endif