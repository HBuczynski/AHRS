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
        void renewProcess(communication::CommunicationProcessMode processMode);

        void switchProcesses();

    private:
        void launchProcess(pid_t &pid, posix_spawn_file_actions_t &action, char *args[]);
        void waitOnProcess(pid_t &pid, posix_spawn_file_actions_t &action);

        utility::Logger& logger_;

        posix_spawn_file_actions_t firstAction_;
        std::pair<pid_t, communication::CommunicationProcessMode> firstCommunicationProcess_;
        posix_spawn_file_actions_t secondAction_;
        std::pair<pid_t, communication::CommunicationProcessMode> secondCommunicationProcess_;
    };
}


#endif //AHRS_COMMUNICATIONPROCESSESHANDLER_H
