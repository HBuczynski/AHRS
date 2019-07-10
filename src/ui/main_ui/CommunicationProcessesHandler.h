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
    using ProcessID = std::tuple<pid_t, config::UICommunicationMode, uint8_t>;

    class CommunicationProcessesHandler
    {
    public:
        CommunicationProcessesHandler();
        ~CommunicationProcessesHandler();

        bool initialize();

        void sendMessage(std::vector<uint8_t>& message, config::UICommunicationMode mode);

        void resetProcess(config::UICommunicationMode mode);
        void restartMasterProcessAndChange();

    private:
        bool initializeFirstProcessMessageQueue();
        bool initializeSecondProcessMessageQueue();

        bool launchCommunicationProcess(config::UICommunicationMode mode, uint8_t processNumber);

        void waitOnProcess(pid_t &pid);

        config::UIMessageQueues uiMessageQueuesParameters_;
        config::UIExecutableFiles uiExecutableFiles_;
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;

        std::shared_ptr<communication::MessageQueueWrapper> firstCommunicationMessageQueue;
        std::shared_ptr<communication::MessageQueueWrapper> secondCommunicationMessageQueue;

        utility::Logger& logger_;
        std::vector<ProcessID> communicationPIDs_;
    };
}


#endif
