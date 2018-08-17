#ifndef AHRS_PROCESSSCHEDULER_H
#define AHRS_PROCESSSCHEDULER_H

#include <cstdint>
#include <atomic>
#include <spawn.h>
#include <map>

#include <logger/Logger.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <config_reader/UIParameters.h>

namespace main_process
{
    class UIApplicationManager
    {
    public:
        UIApplicationManager();
        ~UIApplicationManager();

        bool initialize();

        void startUISystem();
        void stopUISystem();

    private:
        bool initializeMainProcessMessageQueue();
        bool initializeGUIMessageQueue();
        bool initializeFirstProcessMessageQueue();
        bool initializeSecondProcessMessageQueue();
        bool initializeSharedMemory();

        config::UIWirelessCommunication uiWirelessCommunicationParameters_;
        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UISharedMemory uiSharedMemoryParameters_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<boost::interprocess::message_queue> mainMessageQueue;
        std::shared_ptr<boost::interprocess::message_queue> firstCommunicationMessageQueue;
        std::shared_ptr<boost::interprocess::message_queue> secondCommunicationMessageQueue;
        std::shared_ptr<boost::interprocess::message_queue> guiCommunicationMessageQueue;

        std::unique_ptr<boost::interprocess::named_mutex> sharedMemoryMutex_;
        std::unique_ptr<boost::interprocess::shared_memory_object> sharedMemory_;
        std::unique_ptr<boost::interprocess::mapped_region> mappedMemoryRegion_;

        std::atomic<bool> runSystem_;
        utility::Logger& logger_;
    };
}

#endif
