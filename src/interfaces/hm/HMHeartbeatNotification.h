#ifndef AHRS_HMHEARTBEATNOTIFICATION_H
#define AHRS_HMHEARTBEATNOTIFICATION_H

#include "HMNotification.h"
#include <common/HMNodes.h>

namespace communication
{
    class HMHeartbeatNotification final : public HMNotification
    {
    public:
        HMHeartbeatNotification(HMNodes code);
        ~HMHeartbeatNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMNotificationVisitor& visitor) override;

        HMNodes getHMNode() const;
        void setHMNode(HMNodes code);

    private:
        virtual void initializeDataSize() override;

        HMNodes code_;
    };
}


#endif
