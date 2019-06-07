#ifndef HMREGISTERMAINNOTIFICATION_H
#define HMREGISTERMAINNOTIFICATION_H

#include "HMNotification.h"
#include <common/HMNodes.h>

#include <string>

namespace communication
{
    class HMRegisterMainNotification final : public HMNotification
    {
    public:
        HMRegisterMainNotification(HMNodes code, const std::string& queueName, uint32_t size);
        ~HMRegisterMainNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(HMNotificationVisitor& visitor) override;

        HMNodes getHMNode() const;
        void setHMNode(HMNodes code);

        const std::string &getQueueName() const noexcept;
        void setQueueName(const std::string& queueName);

        uint32_t getSize() const noexcept;
        void setSize(uint32_t size);

    private:
        virtual void initializeDataSize() override;

        HMNodes code_;
        std::string queueName_;
        uint32_t size_;
    };
}

#endif // HMREGISTERMAINNOTIFICATION_H
