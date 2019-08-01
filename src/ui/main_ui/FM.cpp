#include "FM.h"

#include <unistd.h>
#include <cstring>
#include <config_reader/ConfigurationReader.h>
#include <interfaces/fm/FMResetCommunicationProcessCommand.h>
#include <interfaces/hm/HMRemoveNodeNotification.h>
#include <interfaces/fm/FMRestartChangeMasterCommand.h>

using namespace redundancy;
using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

FM::FM()
    :   uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
        logger_(Logger::getInstance())
{

}
void FM::initialize()
{
    initializeHMMessageQueue();
    initializeMainMessageQueue();
}

void FM::initializeHMMessageQueue()
{
    try
    {
        hmMessageQueue_ = make_shared<MessageQueueWrapper>(uiMessageQueuesParameters_.hmQueueName, uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- FM:: Communication message queue has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

    }

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-MAIN- FM::Communication message queue has initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }
}

void FM::initializeMainMessageQueue()
{
    try
    {
        mainMessageQueue_ = make_unique<MessageQueueWrapper>(uiMessageQueuesParameters_.mainProcessQueueName, uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- FM:: Communication message queue has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

    }

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-MAIN- FM::Communication message queue has initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }
}

void FM::handeError(const communication::HMErrorCommand& command)
{
    const auto errorType = command.getHMError();

    switch (errorType)
    {
        case HMErrorType::LOST_CONNECTION_COKCPIT_2_FEEDER:
            lostConnection(command.getMode(), command.getSystemState());
            break;
        default:
            break;
    }
}

void FM::lostConnection(config::UICommunicationMode mode, std::string systemMode)
{
    if (mode == UICommunicationMode::MASTER)
    {
        FMRestartChangeMasterCommand command(systemMode);
        auto packet = command.getFrameBytes();
        mainMessageQueue_->send(packet);
    }
    else
    {       
        FMResetCommunicationProcessCommand processReset(UICommunicationMode::REDUNDANT);
        auto packet = processReset.getFrameBytes();
        mainMessageQueue_->send(packet);
    }
}

