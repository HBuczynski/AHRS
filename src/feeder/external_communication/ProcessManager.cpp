#include "ProcessManager.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <interfaces/communication_process_feeder/CalibrationStatusNotification.h>
#include <iostream>

using namespace std;
using namespace utility;
using namespace config;
using namespace communication;
using namespace boost::interprocess;

ProcessManager::ProcessManager()
    :   feederExternalWirelessParameters_(ConfigurationReader::getFeederExternalWireless(FEEDER_PARAMETERS_FILE_PATH)),
        messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
        feederType_(ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH)),
        runConfigurationProcess_(true),
        logger_(Logger::getInstance())
{
    bool isSuccess = true;

    isSuccess = isSuccess & initializeMessageQueueCommunication();
    isSuccess = isSuccess & initializeExternalCommunication();

    if(isSuccess)
    {
        CalibrationStatusNotification notification(CalibrationStatus::PASSED);

        const auto commandFrame = notification.getFrameBytes();
        sendingMessageQueue_->send(commandFrame.data(), commandFrame.size(), 0);
    }
    messageVisitor_.initializeClientUDPManager(clientUDPManager_);
}

ProcessManager::~ProcessManager()
{ }

bool ProcessManager::initializeExternalCommunication()
{
    clientUDPManager_ = make_shared<ClientUDPManager>();

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
                const string message = "ProcessManager: Inappropriate process communication type.";
                logger_.writeLog(LogType::ERROR_LOG, message);
            }

            return false;
        }
    }

    if(logger_.isInformationEnable())
    {
        const string message = "ProcessManager: Initialized external communication process. Process type: " + to_string(static_cast<int>(feederType_.mode));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ProcessManager::initializeMessageQueueCommunication()
{
    try
    {
        receivingMessageQueue_ = make_shared<message_queue>(open_only, messageQueuesParameters_.externalCommunicationQueueName.c_str());
        sendingMessageQueue_ = make_shared<message_queue>(open_only, messageQueuesParameters_.mainProcessQueueName.c_str());
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ProcessManager :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

void ProcessManager::startConfigurationProcess()
{
    unsigned int priority;
    message_queue::size_type receivedSize;

    while(runConfigurationProcess_)
    {
        try
        {
            vector<uint8_t> packet(messageQueuesParameters_.messageSize);
            receivingMessageQueue_->receive(packet.data(), packet.size(), receivedSize, priority);

            packet.resize(receivedSize);
            packet.shrink_to_fit();

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
                    const string message = string("ProcessManager :: Rceived wrong type of message");
                    logger_.writeLog(LogType::ERROR_LOG, message);
                }
            }
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("ProcessManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

    }
}

void ProcessManager::stopConfigurationProcess()
{
    runConfigurationProcess_ = false;
}



