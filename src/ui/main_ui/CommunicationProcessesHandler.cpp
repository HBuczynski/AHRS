#include "CommunicationProcessesHandler.h"
#include <sys/wait.h>

#include <unistd.h>
#include <cstring>

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

extern char **environ;

CommunicationProcessesHandler::CommunicationProcessesHandler()
    :   logger_(Logger::getInstance())
{}

CommunicationProcessesHandler::~CommunicationProcessesHandler()
{
    waitOnProcess(firstCommunicationProcess_.first, firstAction_);
    waitOnProcess(secondCommunicationProcess_.first, secondAction_);
}

void CommunicationProcessesHandler::initializeProcesses()
{
    // First communication process initialization.
    /*char *firstArg1 = const_cast<char*>(COMMUNICATION_BINARY_FILE_NAME.c_str());
    char *firstArg2 = const_cast<char*>(RECEIVING_QUEUE_NAME_FIRST_PROC.c_str());
    char *firstArg3 = const_cast<char*>(SHARED_MEMORY_NAME.c_str());
    char *firstArg4 = const_cast<char*>("MAIN");

    char *firstArgs[] = {firstArg1, firstArg2, firstArg3, firstArg4, NULL};
    launchProcess(firstCommunicationProcess_.first, firstAction_, firstArgs);

    // Second communication process initizalization.
    char *secondArg1 = const_cast<char*>(COMMUNICATION_BINARY_FILE_NAME.c_str());
    char *secondArg2 = const_cast<char*>(RECEIVING_QUEUE_NAME_SECOND_PROC.c_str());
    char *secondArg3 = const_cast<char*>(SHARED_MEMORY_NAME.c_str());
    char *secondArg4 = const_cast<char*>("REDUNDANT");

    char *secondArgs[] = {secondArg1, secondArg2, secondArg3, secondArg4, secondArg4, NULL};
    launchProcess(secondCommunicationProcess_.first, secondAction_, secondArgs);*/
}

void CommunicationProcessesHandler::launchProcess(pid_t &pid, posix_spawn_file_actions_t &action, char *args[])
{
    int status;
    int out[2];

    posix_spawn_file_actions_init(&action);
    pipe(out);
    posix_spawn_file_actions_adddup2(&action, out[1], STDOUT_FILENO);
    posix_spawn_file_actions_addclose(&action, out[0]);

    status = posix_spawn(&pid, args[0], &action, NULL, args, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("MainProcessScheduler :: Process was initialized, process ID: ")
                                   + to_string(pid) + string(" - ") + string(args[3]);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("MainProcessScheduler :: Process was not initialized correctly, process ID: ")
                                   + to_string(pid) + string(" - ") + string(args[3]);;
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
}

void CommunicationProcessesHandler::waitOnProcess(pid_t &pid, posix_spawn_file_actions_t &action)
{
    int status;
    if (waitpid(pid, &status, 0) < 0)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("MainProcessScheduler :: Process ID: ") + to_string(pid) +
                                   string(". Error - ") +  strerror(errno);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
    else
    {
        if (WIFEXITED(status))
        {
            if(logger_.isInformationEnable())
            {
                const string message = string("MainProcessScheduler :: Process ID: ") + to_string(pid) +
                                       string(". Child exit status - ") + to_string(WEXITSTATUS(status));
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
        }
        else
        {
            if(logger_.isInformationEnable())
            {
                const string message = string("MainProcessScheduler :: Process ID: ") + to_string(pid) +
                                       string(". Child process had been finished before waitpid was launched.");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
        }
    }

    posix_spawn_file_actions_destroy(&action);
}

void CommunicationProcessesHandler::renewProcess(CommunicationProcessMode processMode)
{
    terminate(processMode);

    //TODO: parameters of the process. Renew process.
}


void CommunicationProcessesHandler::terminate(CommunicationProcessMode processMode)
{
    pid_t pid;
    if(firstCommunicationProcess_.second == processMode)
    {
        pid = firstCommunicationProcess_.first;
    }
    else
    {
        pid = secondCommunicationProcess_.first;
    }

    if(pid > 0)
    {
        kill(pid, SIGTERM);

        if(logger_.isInformationEnable())
        {
            const string message = string("MainProcessScheduler :: Process was killed, process ID: ") + to_string(pid);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isWarningEnable())
        {
            const string message = string("MainProcessScheduler :: Process tried to be killed second time, process ID: ") + to_string(pid);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void CommunicationProcessesHandler::switchProcesses()
{
    const auto temp = firstCommunicationProcess_.second;
    firstCommunicationProcess_.second = secondCommunicationProcess_.second;
    secondCommunicationProcess_.second = temp;
}

