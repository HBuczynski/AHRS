#ifndef HMREGISTERNOTIFICATION_H
#define HMREGISTERNOTIFICATION_H

#include "HMNotification.h"
#include <common/HMNodes.h>

namespace communication
{
    class HMRegisterNotification final : public HMNotification
    {
    public:
        HMRegisterNotification(HMNodes code);
        ~HMRegisterNotification();

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

#endif // HMREGISTERNOTIFICATION_H
