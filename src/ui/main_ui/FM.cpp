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
        logger_(Logger::getInstance()),
        firstNetCounter_(0),
        secondNetCounter_(0)
{}

void FM::initialize()
{
    initializeHMMessageQueue();
    initializeMainMessageQueue();

    initializeChannels();
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

void FM::initializeChannels()
{
    firstNetChannels_ = {3, 6, 8, 9, 11};
    secondNetChannels_ = {36, 40, 44, 149, 157, 165};
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

void FM::handleInvalidConnection(uint8_t processNumber)
{
    // TO DO
    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- FM:: handleInvalidConnection.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    if (processNumber == config::FIRST_PROCESS)
    {

    }
    else if (processNumber == config::SECOND_PROCESS)
    {

    }
}

