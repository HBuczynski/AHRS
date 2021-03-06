#include "InterManager.h"

#include <interfaces/ethernet_feeder/EthInitConnectionCommand.h>
#include <interfaces/communication_process_feeder/FeederCommandFactory.h>

#include <interfaces/hm/HMRegisterNotification.h>
#include <interfaces/hm/HMHeartbeatNotification.h>
#include <config_reader/ConfigurationReader.h>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

InterManager::InterManager()
    : feederQueuesParameters_(config::ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
      internalCommunicationParameters_(config::ConfigurationReader::getFeederInternalWireless(FEEDER_PARAMETERS_FILE_PATH)),
      connectionEstablishingInterrupt_("FeederInternal"),
      connectionEstablished_(false),
      hmTimerInterrupt_("FeederInternalHM"),
      logger_(Logger::getInstance())
{

    function<void()> callback = bind(&InterManager::launchTimer, this);
    client_ = make_unique<InterClientTCP>(internalCommunicationParameters_.destinationPort, internalCommunicationParameters_.destinationAddress);
    client_->setConnectionCallback(callback);

    server_ = make_unique<EthServerUDP>(internalCommunicationParameters_.sourcePort);
    server_->initializeSharedMemory();

    interCommunicationVisitor_.initializeInterManager(this);
}

InterManager::~InterManager()
{
    hmTimerInterrupt_.stop();
}

bool InterManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeMainMessageQueue();
    isSuccess = isSuccess & initializeCommunicationProcessMessageQueue();

    server_->startListening();

    initializeHMMessageQueue();
    initializeHM();

    launchTimer();

    return isSuccess;
}

bool InterManager::initializeMainMessageQueue()
{
    try
    {
        mainMessageQueue_ = make_unique<MessageQueueWrapper>(feederQueuesParameters_.mainProcessQueueName, feederQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-INTCOM- InterManager:: During openning main queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("-INTCOM- InterManager:: Main massage queue initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool InterManager::initializeCommunicationProcessMessageQueue()
{
    try
    {
       receivingMessageQueue_ = make_unique<MessageQueueWrapper>(feederQueuesParameters_.internalCommunicationQueueName, feederQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-INTCOM- InterManager:: During openning communication queue - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("-INTCOM- InterManager:: Communication massage queue initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool InterManager::initializeHMMessageQueue()
{
    try
    {
        hmMessageQueue_ = make_shared<MessageQueueWrapper>(feederQueuesParameters_.hmQueueName, feederQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-INTCOM- InterManager:: ") + feederQueuesParameters_.hmQueueName + (" queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-INTCOM- InterManager:: Main message queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool InterManager::initializeHM()
{
    if (!hmMessageQueue_)
        return true;

    HMRegisterNotification notification(HMNodes::INTERNAL_FEEDER_COMM);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);

    hmTimerInterrupt_.startPeriodic(HM_INTERVAL_MS, this);

    return true;
}

bool InterManager::connectToFeeder()
{
    auto command = make_unique<EthInitConnectionCommand>(internalCommunicationParameters_.sourcePort, internalCommunicationParameters_.sourceAddress);

    if(client_->connectToServer())
    {
        client_->startCommandSending();
        sendCommands(move(command));
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-INTCOM- InterManager:: Cannot connect to server.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        return false;
    }
    return true;
}

void InterManager::startCommunication()
{
    FeederCommandFactory commandFactory;

    while(runCommunicationProcess_)
    {
        try
        {
            const auto packet = receivingMessageQueue_->receive();

            if (!packet.empty())
            {
                const auto command = commandFactory.createCommand(packet);
                command->accept(interCommunicationVisitor_);
            }
        }
        catch(interprocess_exception &ex)
        {
            if ( logger_.isErrorEnable())
            {
                const string message = string("-INTCOM- ProcessManager:: Receiving data ::") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void InterManager::stopCommunication()
{
    runCommunicationProcess_ = false;
}

void InterManager::launchTimer()
{
    connectionEstablished_ = false;
    connectionEstablishingInterrupt_.startPeriodic(5000, this);
}

void InterManager::interruptNotification(timer_t timerID)
{
    if(timerID == hmTimerInterrupt_.getTimerID())
        sendHeartbeat();

    if(timerID == connectionEstablishingInterrupt_.getTimerID())
        initConnection();
}

void InterManager::sendHeartbeat()
{
    HMHeartbeatNotification notification(HMNodes::INTERNAL_FEEDER_COMM);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);
}

void InterManager::initConnection()
{
    if(!connectionEstablished_)
    {
        if (connectToFeeder())
        {
            connectionEstablished_ = true;

            if(logger_.isInformationEnable())
            {
                const string message = string("-INTCOM- InterManager:: Connection established.");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
        }
    }
    else
    {
        connectionEstablishingInterrupt_.stop();
    }
}

void InterManager::sendCommands(unique_ptr<EthFeederCommand> command)
{
    client_->sendCommand(move(command));
}
