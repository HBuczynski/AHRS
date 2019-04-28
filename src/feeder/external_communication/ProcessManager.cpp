#include "ProcessManager.h"

#include <interfaces/communication_process_feeder/CalibrationStatusNotification.h>
#include <interfaces/communication_process_feeder/StateNotification.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

#include <functional>
#include <iostream>

using namespace std;
using namespace utility;
using namespace config;
using namespace communication;
using namespace boost::interprocess;

ProcessManager::ProcessManager(const string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
    :   feederExternalWirelessParameters_(ConfigurationReader::getFeederExternalWireless(FEEDER_PARAMETERS_FILE_PATH)),
        messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
        feederType_(ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH)),
        runConfigurationProcess_(true),
        logger_(Logger::getInstance())
{
    clientUDPManager_ = make_shared<ClientUDPManager>(name, transitionTable, rootState);

    function<void(std::vector<uint8_t>&)> callback = bind(&ProcessManager::sendMessageToMainProcess, this, std::placeholders::_1);
    clientUDPManager_->registerCallbackToMainProc(callback);
}

bool ProcessManager::initialize()
{
    bool isSuccess = true;

    isSuccess = isSuccess & initializeMessageQueueCommunication();
    isSuccess = isSuccess & initializeWirelesslCommunication();

    // Send information to Main Process
    auto notification = StateNotification(FeederStateCode::REGISTERED_USERS);
    auto packet = notification.getFrameBytes();
    sendMessageToMainProcess(packet);

    return isSuccess;
}

bool ProcessManager::initializeWirelesslCommunication()
{
    switch (feederType_.processNumber)
    {
        case 1 :
        {
            server_ = make_shared<ServerTCP>(feederExternalWirelessParameters_.firstPort, feederExternalWirelessParameters_.maxUserNumber, clientUDPManager_);
            server_->startUserActivation();
            break;
        }
        case 2 :
        {
            server_ = make_shared<ServerTCP>(feederExternalWirelessParameters_.secondPort, feederExternalWirelessParameters_.maxUserNumber, clientUDPManager_);
            server_->startUserActivation();
            break;
        }
        default:
        {
            if(logger_.isErrorEnable())
            {
                const string message = "-EXTCOM- ProcessManager: Inappropriate process communication type.";
                logger_.writeLog(LogType::ERROR_LOG, message);
            }

            return false;
        }
    }

    if(logger_.isInformationEnable())
    {
        const string message = "-EXTCOM- ProcessManager: Initialized external communication process. Process type: " + to_string(static_cast<int>(feederType_.mode));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ProcessManager::initializeMessageQueueCommunication()
{
    try
    {
        receivingMessageQueue_ = make_shared<MessageQueueWrapper>(messageQueuesParameters_.externalCommunicationQueueName, messageQueuesParameters_.messageSize);
        sendingMessageQueue_ = make_shared<MessageQueueWrapper>(messageQueuesParameters_.mainProcessQueueName, messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-EXTCOM- ProcessManager :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

void ProcessManager::start()
{
    clientUDPManager_->startHSM();

    while(runConfigurationProcess_)
    {
        try
        {
            const auto packet = receivingMessageQueue_->receive();
            const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

            if(frameType == FrameType::COMMAND)
            {
                const auto command = commandFactory_.createCommand(packet);
                command->accept(messageVisitor_);
            }
            else if (frameType == FrameType::NOTIFICATION)
            {
                const auto notification = notificationFactory_.createNotification(packet);
                notification->accept(messageVisitor_);
            }
            else
            {
                if(logger_.isErrorEnable())
                {
                    const string message = string("-EXTCOM- ProcessManager :: Rceived wrong type of message");
                    logger_.writeLog(LogType::ERROR_LOG, message);
                }
            }
        }
        catch(exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-EXTCOM- ProcessManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void ProcessManager::stop()
{
    runConfigurationProcess_ = false;
}

void ProcessManager::sendMessageToMainProcess(vector<uint8_t> &data)
{
    sendingMessageQueue_->send(data);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("-EXTCOMM- ProcessManager:: Send msg to main process.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}



