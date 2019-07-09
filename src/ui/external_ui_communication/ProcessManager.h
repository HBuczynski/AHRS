#ifndef AHRS_PROCESSMANAGER_H
#define AHRS_PROCESSMANAGER_H

#include <message_queue_wrapper/MessageQueueWrapper.h>

#include <thread>
#include <memory>
#include <atomic>

#include "MainProcessHandlerVisitor.h"
#include "CommunicationManagerUI.h"
#include <interfaces/communication_process_ui/UICommandFactory.h>
#include <interfaces/communication_process_ui/UICommandVisitor.h>

#include <time_manager/TimerInterrupt.h>
#include <common/UIStates.h>
#include <logger/Logger.h>

namespace communication
{
    class ProcessManager final : public utility::TimerInterruptNotification
    {
    public:
        ProcessManager(uint8_t mode, uint8_t processNumber, const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);
        ~ProcessManager();

        bool initialize();

        void startCommunication();
        void stopCommunication();

        void setState(UIExternalComCode code);

     private:

        bool initializeMainMessageQueue();
        bool initializeHMMessageQueue();
        bool initializeCommunicationProcessMessageQueue();
        bool initializeSharedMemory();
        bool initializeWirelessCommunication();

        void initInformation();
        bool initializeHM();

        void interruptNotification(timer_t timerID);

        void handleMessageQueue(const std::vector<uint8_t> &data);
        void sendMessageToMainProcess(std::vector<uint8_t > &data);
        void sendMessageToHMProcess(std::vector<uint8_t > &data);


        config::UICommunicationMode mode_;
        uint8_t processNumber_;

        UIExternalComCode communicationState_;
        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        communication::UICommandFactory uiCommandFactory_;
        std::shared_ptr<CommunicationManagerUI> communicationManagerUI_;
        std::unique_ptr<MainProcessHandlerVisitor> mainProcessHandlerVisitor_;

        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::unique_ptr<communication::MessageQueueWrapper> sendingMessageQueue_;
        std::unique_ptr<communication::MessageQueueWrapper> receivingMessageQueue_;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        std::atomic<bool> runCommunicationProcess_;
        utility::TimerInterrupt timerInterrupt_;
        utility::Logger& logger_;
    };
}

#endif
