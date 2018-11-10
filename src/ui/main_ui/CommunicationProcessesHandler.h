#ifndef AHRS_COMMUNICATIONPROCESSESHANDLER_H
#define AHRS_COMMUNICATIONPROCESSESHANDLER_H

#include <utility>
#include <string>
#include <cstdint>
#include <spawn.h>
#include <cstdint>
#include <atomic>

#include <logger/Logger.h>
#include <config_reader/UIParameters.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

namespace main_process
{
    using ProcessID = std::pair<pid_t, config::UICommunicationMode>;

    class CommunicationProcessesHandler
    {
    public:
        CommunicationProcessesHandler();
        ~CommunicationProcessesHandler();

        bool initialize();

        void sendMessage(std::vector<uint8_t>& message, config::UICommunicationMode mode);

        void resetProcess(uint8_t processNumber);
        void switchProcesses();

    private:
        bool initializeFirstProcessMessageQueue();
        bool initializeSecondProcessMessageQueue();

        bool launchFirstProcess();
        bool launchSecondProcess();

        void waitOnProcess(pid_t &pid, posix_spawn_file_actions_t &action);

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UIExecutableFiles uiExecutableFiles_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<communication::MessageQueueWrapper> firstCommunicationMessageQueue;
        std::shared_ptr<communication::MessageQueueWrapper> secondCommunicationMessageQueue;

        utility::Logger& logger_;
        std::map<uint8_t, ProcessID> externallProcessess_;
    };
}


#endif
