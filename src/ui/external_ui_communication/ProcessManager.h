#ifndef AHRS_PROCESSMANAGER_H
#define AHRS_PROCESSMANAGER_H

#include <boost/interprocess/ipc/message_queue.hpp>

#include <thread>
#include <memory>
#include <atomic>

#include "CommunicationManagerUI.h"
#include <interfaces/communication_process_ui/UICommandFactory.h>
#include <interfaces/communication_process_ui/UICommandVisitor.h>

#include <logger/Logger.h>

namespace communication
{
    class ProcessManager
    {
    public:
        ProcessManager(uint8_t processNumber);
        ~ProcessManager();

        bool initialize();
        
        void startCommunication();
        void stopCommunication();

    private:

        bool initializeMainMessageQueue();
        bool initializeCommunicationProcessMessageQueue();
        bool initializeSharedMemory();
        bool initializeWirelessCommunication();

        void handleMessage(const std::vector<uint8_t > &data);

        uint8_t processNumber_;

        config::UIWirelessCommunication uiWirelessCommunicationParameters_;
        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        communication::UICommandFactory uiCommandFactory_;
        std::shared_ptr<CommunicationManagerUI> communicationManagerUI_;

        std::unique_ptr<boost::interprocess::message_queue> sendingMessageQueue_;
        std::unique_ptr<boost::interprocess::message_queue> receivingMessageQueue_;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        std::atomic<bool> runCommunicationProcess_;
        utility::Logger& logger_;
    };
}

#endif