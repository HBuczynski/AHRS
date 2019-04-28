#include "CommunicationProcessesHandler.h"
#include <sys/wait.h>

#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;

CommunicationProcessesHandler::CommunicationProcessesHandler()
    :   uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
        uiExecutableFiles_(config::ConfigurationReader::getUIExecutableFiles(UI_PARAMETERS_FILE_PATH)),
        uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH)),
        logger_(Logger::getInstance())
{}

CommunicationProcessesHandler::~CommunicationProcessesHandler()
{
    //waitOnProcess(firstCommunicationProcess_.first, firstAction_);
    //waitOnProcess(secondCommunicationProcess_.first, secondAction_);
}

bool CommunicationProcessesHandler::initialize()
{
    bool isSuccess = true;

    isSuccess = isSuccess & initializeFirstProcessMessageQueue();
    isSuccess = isSuccess & initializeSecondProcessMessageQueue();
    isSuccess = isSuccess & launchFirstProcess();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    isSuccess = isSuccess & launchSecondProcess();

    return isSuccess;
}

bool CommunicationProcessesHandler::initializeFirstProcessMessageQueue()
{
    try
    {
        firstCommunicationMessageQueue = make_shared<MessageQueueWrapper>(uiMessageQueuesParameters_.firstCommunicationQueueName,
                                                                        uiMessageQueuesParameters_.messageQueueNumber,
                                                                        uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: First communication message queue has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: First communication message queue has initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool CommunicationProcessesHandler::initializeSecondProcessMessageQueue()
{
    try
    {
        secondCommunicationMessageQueue = make_shared<MessageQueueWrapper>(uiMessageQueuesParameters_.secondCommunicationQueueName,
                                                                        uiMessageQueuesParameters_.messageQueueNumber,
                                                                        uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: Second communication message queue has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: Second communication message queue has initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool CommunicationProcessesHandler::launchFirstProcess()
{
    char *firstArg1 = const_cast<char*>(uiExecutableFiles_.externalCommunicationProcess.c_str());
    string processNumber = to_string(1);
    char *firstArg2 = const_cast<char*>(processNumber.c_str());
    char *arguments[] = {firstArg1, firstArg2, NULL};

    ProcessID firstProcess;

    int status;
    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);

    status = posix_spawn(&firstProcess.first, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- CommunicationProcessesHandler :: First process was initialized, process ID: ") + to_string(firstProcess.first);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("CommunicationProcessesHandler :: First process was not initialized correctly, process ID: ") + to_string(firstProcess.first);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if(uiCommunicationSystemParameters_.firstProcess.mode == UICommunicationMode::MASTER)
    {
        firstProcess.second = UICommunicationMode::MASTER;
    }
    else
    {
        firstProcess.second = UICommunicationMode::REDUNDANT;
    }

    externallProcessess_[1] = firstProcess;

    return true;
}

bool CommunicationProcessesHandler::launchSecondProcess()
{
    char *secondArg1 = const_cast<char*>(uiExecutableFiles_.externalCommunicationProcess.c_str());
    string processNumber = to_string(2);
    char *secondArg2 = const_cast<char*>(processNumber.c_str());
    char *arguments[] = {secondArg1, secondArg2, NULL};

    ProcessID secondProcess;

    int status;

    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);

    status = posix_spawn(&secondProcess.first, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- CommunicationProcessesHandler:: Second process was initialized, process ID: ") + to_string(secondProcess.first);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- CommunicationProcessesHandler:: Second process was not initialized correctly, process ID: ") + to_string(secondProcess.first);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if(uiCommunicationSystemParameters_.firstProcess.mode == UICommunicationMode::MASTER)
    {
        secondProcess.second = UICommunicationMode::MASTER;
    }
    else
    {
        secondProcess.second = UICommunicationMode::REDUNDANT;
    }

    externallProcessess_[2] = secondProcess;

    return true;
}

void CommunicationProcessesHandler::waitOnProcess(pid_t &pid, posix_spawn_file_actions_t &action)
{
    int status;
    if (waitpid(pid, &status, 0) < 0)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- CommunicationProcessesHandler :: Process ID: ") + to_string(pid) +
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
                const string message = string("-MAIN- CommunicationProcessesHandler :: Process ID: ") + to_string(pid) +
                                       string(". Child changePage status - ") + to_string(WEXITSTATUS(status));
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
        }
        else
        {
            if(logger_.isInformationEnable())
            {
                const string message = string("-MAIN- CommunicationProcessesHandler :: Process ID: ") + to_string(pid) +
                                       string(". Child process had been finished before waitpid was launched.");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
        }
    }

    posix_spawn_file_actions_destroy(&action);
}

void CommunicationProcessesHandler::resetProcess(uint8_t processNumber)
{

}

void CommunicationProcessesHandler::switchProcesses()
{

}

void CommunicationProcessesHandler::sendMessage(std::vector<uint8_t> &message, config::UICommunicationMode mode)
{
    const auto processNumber = std::find_if(externallProcessess_.begin(), externallProcessess_.end(), [&mode](decltype(*externallProcessess_.begin()) &iter)
    {
        return iter.second.second == mode;
    });

    if((*processNumber).first == 1)
    {
        firstCommunicationMessageQueue->send(message);
    }
    else
    {
        secondCommunicationMessageQueue->send(message);
    }

}

