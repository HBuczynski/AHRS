#ifndef AHRS_COMMUNICATIONPROCESSESHANDLER_H
#define AHRS_COMMUNICATIONPROCESSESHANDLER_H

#include <utility>
#include <string>
#include <cstdint>
#include <spawn.h>
#include <cstdint>
#include <atomic>

#include <logger/Logger.h>
#include <communication_process/ProcessManager.h>

namespace main_process
{
    class CommunicationProcessesHandler
    {
    public:
        CommunicationProcessesHandler();
        ~CommunicationProcessesHandler();

        void initializeProcesses();
        void terminate(communication::CommunicationProcessMode processMode);
        void switchProcesses();

    private:
        void launchProcess(pid_t &pid, posix_spawn_file_actions_t &action, char *args[]);
        void waitOnProcess(pid_t &pid, posix_spawn_file_actions_t &action);

        utility::Logger& logger_;

        posix_spawn_file_actions_t firstAction_;
        std::pair<pid_t, communication::CommunicationProcessMode> firstCommunicationProcess_;
        posix_spawn_file_actions_t secondAction_;
        std::pair<pid_t, communication::CommunicationProcessMode> secondCommunicationProcess_;

        const std::string COMMUNICATION_BINARY_FILE_NAME = "communication_process_ui";
        const std::string MANAGEMENT_QUEUE_NAME = "managementQueue";
        const std::string SENDING_QUEUE_NAME_FIRST_PROC = "sendingQueueFirst";
        const std::string SENDING_QUEUE_NAME_SECOND_PROC = "sendingQueueSecond";
        const std::string SHARED_MEMORY_NAME = "sharedMmeory";
    };
}


#endif //AHRS_COMMUNICATIONPROCESSESHANDLER_H
