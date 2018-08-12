#include "ProcessManager.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
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
        logger_(Logger::getInstance())
{
    initializeMessageQueueCommunication();
    initializeExternalCommunication();

    messageVisitor_.initializeClientUDPManager(clientUDPManager_);
}

ProcessManager::~ProcessManager()
{ }

void ProcessManager::initializeExternalCommunication()
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
            break;
        }
    }

    if(logger_.isInformationEnable())
    {
        const string message = "ProcessManager: Initialized external communication process. Process type: " + to_string(static_cast<int>(feederType_.mode));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ProcessManager::initializeMessageQueueCommunication()
{
    try
    {
        message_queue::remove(messageQueuesParameters_.externalCommunicationQueueName.c_str());
        receivingMessageQueue = make_shared<message_queue>(open_or_create,
                                                  messageQueuesParameters_.externalCommunicationQueueName.c_str(),
                                                  messageQueuesParameters_.messageQueueNumber,
                                                  messageQueuesParameters_.messageSize);
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

void ProcessManager::runProcessConfiguration()
{
    unsigned int priority;
    message_queue::size_type receivedSize;

    while(true)
    {
        try
        {
            vector<uint8_t> packet(messageQueuesParameters_.messageSize);
            receivingMessageQueue->receive(packet.data(), packet.size(), receivedSize, priority);

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




