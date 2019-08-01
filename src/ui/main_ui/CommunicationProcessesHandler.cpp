#include "CommunicationProcessesHandler.h"
#include <sys/wait.h>

#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <config_reader/ConfigurationReader.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>
#include <interfaces/communication_process_ui/UIChangeModeCommand.h>
#include <interfaces/wireless_commands/ChangeFeederModeCommand.h>
#include <interfaces/wireless_commands/StartAcquisitionCommand.h>

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
    isSuccess = isSuccess & launchCommunicationProcess(UICommunicationMode::MASTER, FIRST_PROCESS);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    isSuccess = isSuccess & launchCommunicationProcess(UICommunicationMode::REDUNDANT, SECOND_PROCESS);

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

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: First communication message queue has initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
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

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: Second communication message queue has initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }

    return true;
}

bool CommunicationProcessesHandler::launchCommunicationProcess(UICommunicationMode mode, uint8_t processNumber)
{
    char *arg1 = const_cast<char*>(uiExecutableFiles_.externalCommunicationProcess.c_str());

    string modeNumber = to_string(static_cast<uint8_t>(mode));
    char *arg2 = const_cast<char*>(modeNumber.c_str());

    string processNumberString = to_string(processNumber);
    char *arg3 = const_cast<char*>(processNumberString.c_str());

    char *arguments[] = {arg1, arg2, arg3, NULL};

    ProcessID processID;
    pid_t pid;

    int status;
    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);

    status = posix_spawn(&pid, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- CommunicationProcessesHandler :: Process was initialized, process ID: ") + to_string(pid);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("CommunicationProcessesHandler :: Process was not initialized correctly, process ID: ") + to_string(pid);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    processID = make_tuple(pid, mode, processNumber);
    communicationPIDs_.push_back(processID);

    return true;
}

void CommunicationProcessesHandler::waitOnProcess(pid_t &pid)
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
}

void CommunicationProcessesHandler::resetProcess(UICommunicationMode mode)
{
    // Kill process
    const auto processIter = std::find_if(communicationPIDs_.begin(), communicationPIDs_.end(), [&mode](decltype(*communicationPIDs_.begin()) &iter)
    {
        return std::get<1>(iter) == mode;
    });

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ") + to_string(std::get<0>(*processIter)) +"\t"+ to_string(std::get<1>(*processIter)) + "\t" + to_string(std::get<2>(*processIter));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    const auto command = "sudo kill -9 " + to_string(std::get<0>(*processIter));
    system(command.c_str());
    waitOnProcess(std::get<0>(*processIter));

    uint8_t processNumber = get<2>(*processIter);
    communicationPIDs_.erase(processIter);

    launchCommunicationProcess(mode, processNumber);
}

void CommunicationProcessesHandler::restartMasterProcessAndChange(std::string systemState)
{
    const auto processIter = std::find_if(communicationPIDs_.begin(), communicationPIDs_.end(), [](decltype(*communicationPIDs_.begin()) &iter)
    {
        return std::get<1>(iter) == UICommunicationMode::MASTER;
    });

    const auto command = "sudo kill -9 " + to_string(std::get<0>(*processIter));
    system(command.c_str());
    waitOnProcess(std::get<0>(*processIter));

//    for(auto iter: communicationPIDs_)
//        cout << "Process: " << to_string(static_cast<int>(std::get<2>(iter))) << "\t mode: " << to_string(static_cast<int>(std::get<1>(iter))) << endl;


    uint8_t processNumber = get<2>(*processIter);
    communicationPIDs_.erase(processIter);

    // Change REDUNDANT Process to master.
    const auto redundantIter = std::find_if(communicationPIDs_.begin(), communicationPIDs_.end(), [](decltype(*communicationPIDs_.begin()) &iter)
    {
        return std::get<1>(iter) == UICommunicationMode::REDUNDANT;
    });

    std::get<1>(*redundantIter) = UICommunicationMode::MASTER;

    UIChangeModeCommand changeCommand(UICommunicationMode::MASTER);
    auto packet = changeCommand.getFrameBytes();
    sendMessage(packet, UICommunicationMode::MASTER);

    ChangeFeederModeCommand modeCommand(FeederMode::MASTER);
    auto commandWrapper = SendingDataCommand(modeCommand.getFrameBytes());
    auto commandPacket = commandWrapper.getFrameBytes();
    sendMessage(commandPacket, UICommunicationMode::MASTER);

    if(systemState == "AcquisitionState")
    {
        StartAcquisitionCommand startAcqCommand;
        auto startWrapper = SendingDataCommand(startAcqCommand.getFrameBytes());
        auto startWrapperPacket = startWrapper.getFrameBytes();
        sendMessage(startWrapperPacket, UICommunicationMode::MASTER);
    }

    // Relaunch new redundant process
    launchCommunicationProcess(UICommunicationMode::REDUNDANT, processNumber);
}

void CommunicationProcessesHandler::sendMessage(std::vector<uint8_t> &message, config::UICommunicationMode mode)
{
    const auto processIter = std::find_if(communicationPIDs_.begin(), communicationPIDs_.end(), [&mode](decltype(*communicationPIDs_.begin()) &iter)
    {
        return std::get<1>(iter) == mode;
    });

//    for(auto iter: communicationPIDs_)
//        cout << "Process: " << to_string(static_cast<int>(std::get<2>(iter))) << "\t mode: " << to_string(static_cast<int>(std::get<1>(iter))) << endl;

    if(std::get<2>(*processIter) == FIRST_PROCESS)
    {
        firstCommunicationMessageQueue->send(message);
    }
    else
    {
        secondCommunicationMessageQueue->send(message);
    }

}

