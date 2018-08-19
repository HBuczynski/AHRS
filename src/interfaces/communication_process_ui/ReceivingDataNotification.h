#ifndef AHRS_RECEIVINGDATANOTIFICATION_H
#define AHRS_RECEIVINGDATANOTIFICATION_H

#include "UINotification.h"

namespace communication
{
    class ReceivingDataNotification : public UINotification
    {
    public:
        ReceivingDataNotification(const std::vector<uint8_t> &data);
        ~ReceivingDataNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(UINotificationVisitor& visitor) override;

        const std::vector<uint8_t>& getData() const;
        void setData(const std::vector<uint8_t> &data);

    private:
        virtual void initializeDataSize() override;

        std::vector<uint8_t> data_;
    };
}

#endif