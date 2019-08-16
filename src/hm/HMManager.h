#ifndef HMMANAGER_H
#define HMMANAGER_H

#include <interfaces/hm/HMNotificationVisitor.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <time_manager/TimerInterrupt.h>

#include <logger/Logger.h>
#include <common/HMNodes.h>
#include <unordered_map>

#include <mutex>
#include <string>
#include <chrono>

namespace hm
{
    using TimePoint = std::chrono::steady_clock::time_point;

    class HMManager final : public communication::HMNotificationVisitor, public utility::TimerInterruptNotification
    {
    public:
        HMManager();
        ~HMManager();

        bool initialize(const std::string &name);
        void run();

        virtual void visit(const communication::HMRegisterNotification& command) override;
        virtual void visit(const communication::HMHeartbeatNotification& command) override;
        virtual void visit(const communication::HMRegisterMainNotification& command) override;
        virtual void visit(const communication::HMErrorNotification& command) override;
        virtual void visit(const communication::HMRemoveNodeNotification& command) override;
        virtual void visit(const communication::HMInvalidConnectionNotification &command) override;

    private:
        void interruptNotification(timer_t timerID) override;

        bool initializeMainQueue(std::string name, uint32_t size);
        bool initializeHMQueue(std::string name, uint32_t queueNumber, uint32_t size);

        void updateTable();
        void sendToMainProcess(std::function<void(std::vector<uint8_t>&)> callback);

        std::map<HMNodes, TimePoint> nodesContainer_;

        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> mainMessageQueue_;

        bool runHM_;
        std::mutex containerMutex_;

        utility::TimerInterrupt timerInterrupt_;
        utility::Logger& logger_;

        const uint16_t HM_THRESHOLD_MS = HM_INTERVAL_MS;
    };
}

#endif // HMMANAGER_H
