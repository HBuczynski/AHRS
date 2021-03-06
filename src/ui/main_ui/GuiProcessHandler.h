#ifndef AHRS_GUIPROCESSHANDLER_H
#define AHRS_GUIPROCESSHANDLER_H

#include <utility>
#include <string>
#include <cstdint>
#include <spawn.h>
#include <cstdint>
#include <atomic>
#include <vector>

#include <logger/Logger.h>
#include <config_reader/UIParameters.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

namespace main_process
{
    class GuiProcessHandler
    {
    public:
        GuiProcessHandler();
        ~GuiProcessHandler();

        bool initialize();
        void sendMessage(std::vector<uint8_t>& message);
        void resetProcess();

    private:
        bool initializeMessageQueue();
        bool launchProcess();

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UIExecutableFiles uiExecutableFiles_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<communication::MessageQueueWrapper> communicationMessageQueue;

        pid_t pid;
        utility::Logger& logger_;
    };
}

#endif
