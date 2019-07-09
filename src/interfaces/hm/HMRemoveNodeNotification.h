#ifndef HMREMOVENODENOTIFICATION_H
#define HMREMOVENODENOTIFICATION_H

#include "HMNotification.h"
#include <common/HMNodes.h>

namespace communication
{
    class HMRemoveNodeNotification final : public HMNotification
    {
    public:
        HMRemoveNodeNotification(HMNodes code);
        ~HMRemoveNodeNotification();

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

#endif // HMREMOVENODENOTIFICATION_H
