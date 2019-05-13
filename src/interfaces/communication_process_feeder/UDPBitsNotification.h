#ifndef UDPBITSNOTIFICATION_H
#define UDPBITSNOTIFICATION_H

#include "FeederNotification.h"

namespace communication
{
    enum BITS_ACTION : uint8_t
    {
        SEND_DEMAND = 0x05,
        RECEIVED_ACQ = 0x10
    };

    class UDPBitsNotification final : public FeederNotification
    {
    public:
        UDPBitsNotification(BITS_ACTION code);
        ~UDPBitsNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederNotificationVisitor& visitor) override;

        BITS_ACTION getActionCode() const;
        void setActionCode(BITS_ACTION code);

    private:
        virtual void initializeDataSize() override;

        BITS_ACTION code_;
    };
}


#endif // UDPBITSNOTIFICATION_H
