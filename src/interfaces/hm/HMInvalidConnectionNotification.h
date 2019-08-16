#ifndef HMINVALIDCONNECTIONNOTIFICATION_H
#define HMINVALIDCONNECTIONNOTIFICATION_H

#include "HMNotification.h"

namespace communication
{
    class HMInvalidConnectionNotification final : public HMNotification
    {
    public:
        HMInvalidConnectionNotification(uint8_t processNumber);
        ~HMInvalidConnectionNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMNotificationVisitor& visitor) override;

        uint8_t getProcessNumber() const;
        void setProcessNumber(const uint8_t &processNumber);

    private:
        virtual void initializeDataSize() override;

        uint8_t processNumber_;
    };
}

#endif // HMINVALIDCONNECTIONNOTIFICATION_H
