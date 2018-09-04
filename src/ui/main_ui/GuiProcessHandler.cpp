#include "GuiProcessHandler.h"

#include <sys/wait.h>

#include <unistd.h>
#include <cstring>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace main_process;
using namespace boost::interprocess;

GuiProcessHandler::GuiProcessHandler()
    :   uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
        uiExecutableFiles_(config::ConfigurationReader::getUIExecutableFiles(UI_PARAMETERS_FILE_PATH)),
        uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH)),
        logger_(Logger::getInstance())
{ }

GuiProcessHandler::~GuiProcessHandler()
{}

bool GuiProcessHandler::initialize()
{
    bool isSuccess = true;

    isSuccess = isSuccess & initializeMessageQueue();
    isSuccess = isSuccess & launchProcess();

    return isSuccess;
}

void GuiProcessHandler::resetProcess()
{

}

bool GuiProcessHandler::initializeMessageQueue()
{
    try
    {
        message_queue::remove(uiMessageQueuesParameters_.guiProcessQueueName.c_str());
        communicationMessageQueue = make_shared<message_queue>(create_only, uiMessageQueuesParameters_.guiProcessQueueName.c_str(),
                uiMessageQueuesParameters_.messageQueueNumber,
                uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("GuiProcessHandler:: Communication message queue has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("GuiProcessHandler::Communication message queue has initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool GuiProcessHandler::launchProcess()
{
    char *secondArg1 = const_cast<char*>(uiExecutableFiles_.guiProcess.c_str());
    char *arguments[] = {secondArg1,  NULL};

    int status;
    int out[2];

    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);
    pipe(out);
    posix_spawn_file_actions_adddup2(&action, out[1], STDOUT_FILENO);
    posix_spawn_file_actions_addclose(&action, out[0]);

    status = posix_spawn(&pid, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("GuiProcessHandler:: GUI process was initialized.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("GuiProcessHandler:: GUI process was not initialized correctly.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}
