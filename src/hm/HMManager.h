#ifndef HMMANAGER_H
#define HMMANAGER_H

#include <interfaces/hm/HMNotificationVisitor.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

#include <logger/Logger.h>
#include <common/HMNodes.h>
#include <unordered_map>

#include <string>
#include <chrono>

namespace hm
{
    using TimePoint = std::chrono::system_clock::time_point;

    class HMManager : public communication::HMNotificationVisitor
    {
    public:
        HMManager();
        ~HMManager();

        bool initialize(const std::string &name);
        void run();

        virtual void visit(const communication::HMRegisterNotification& command) override;
        virtual void visit(const communication::HMHeartbeatNotification& command) override;
        virtual void visit(const communication::HMRegisterMainNotification& command) override;

    private:
        bool initializeMainQueue(std::string name, uint32_t size);
        bool initializeHMQueue(std::string name, uint32_t queueNumber, uint32_t size);

        std::unordered_map<HMNodes, TimePoint> nodesContainer_;

        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> mainMessageQueue_;

        bool runHM_;
        utility::Logger& logger_;
    };
}

#endif // HMMANAGER_H
