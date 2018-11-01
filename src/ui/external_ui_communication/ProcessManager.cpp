#include "ProcessManager.h"
#include <interfaces/wireless_commands/Command.h>

#include <config_reader/ConfigurationReader.h>
#include <interfaces/wireless_commands/PerformBITsCommand.h>
#include <interfaces/communication_process_ui/CommunicationStatusNotification.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

ProcessManager::ProcessManager(uint8_t processNumber)
    : processNumber_(processNumber),
      uiWirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH.c_str())),
      uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
      uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH.c_str())),
      uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH.c_str())),
      communicationManagerUI_(make_shared<CommunicationManagerUI>(processNumber_)),
      mainProcessHandlerVisitor_(make_unique<MainProcessHandlerVisitor>(communicationManagerUI_)),
      connectionEstablished_(false),
      runCommunicationProcess_(true),
      logger_(Logger::getInstance())
{ }

ProcessManager::~ProcessManager()
{ }

bool ProcessManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeMainMessageQueue();
    isSuccess = isSuccess & initializeCommunicationProcessMessageQueue();
    isSuccess = isSuccess & initializeSharedMemory();
    isSuccess = isSuccess & initializeWirelessCommunication();
    connectToFeeder();

    return isSuccess;
}

bool ProcessManager::initializeMainMessageQueue()
{
    try
    {
        sendingMessageQueue_ = make_unique<message_queue>(open_only, uiMessageQueuesParameters_.mainProcessQueueName.c_str());
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ProcessManager:: Process - ") + to_string(processNumber_) +". During openning main queue - " + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Main massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ProcessManager::initializeCommunicationProcessMessageQueue()
{
    try
    {
        if(processNumber_ == 1)
        {
            receivingMessageQueue_ = make_unique<message_queue>(open_only, uiMessageQueuesParameters_.firstCommunicationQueueName.c_str());
        }
        else if(processNumber_ == 2)
        {
            receivingMessageQueue_ = make_unique<message_queue>(open_only, uiMessageQueuesParameters_.secondCommunicationQueueName.c_str());
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". False process number.";
                logger_.writeLog(LogType::ERROR_LOG, message);
            }

            return false;
        }

    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ProcessManager:: Process - ") + to_string(processNumber_) +". During openning communication queue ::" + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Communication massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ProcessManager::initializeSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        sharedMemoryMutex_ = std::make_unique<named_mutex>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str());
        // Creating shared memory.
        sharedMemory_ = std::make_unique<shared_memory_object>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str(), read_write);
        mappedMemoryRegion_ = std::make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Shared memory has not been initialized correctly.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Shared memory has been initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool ProcessManager::initializeWirelessCommunication()
{
    if(communicationManagerUI_->initializeServer())
    {
        if (logger_.isInformationEnable())
        {
            const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Communication Manager UI has been initialized correctly.";
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return true;
    }
    else
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Communication Manager UI has not been initialized correctly.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
}

void ProcessManager::connectToFeeder()
{
    connectionEstablishingInterrupt_.startPeriodic(1000, this);
//    if(!connectionEstablished_)
//    {
//        //if ( connectionEstablishingInterrupt_.getTimerID() == timerID )
//        {
//            if ( communicationManagerUI_->connectToFeeder())
//            {
//                auto notification = CommunicationStatusNotification(communicationManagerUI_->getCurrentState(), communicationManagerUI_->getProcessNumber());
//                sendMessageToMainProcess(notification.getFrameBytes());
//
//                connectionEstablished_ = true;
//            }
//        }
//    }
//    else
//    {
//        connectionEstablishingInterrupt_.stop();
//    }
}

void ProcessManager::interruptNotification(timer_t timerID)
{
    if(!connectionEstablished_)
    {
        if ( connectionEstablishingInterrupt_.getTimerID() == timerID )
        {
            if ( communicationManagerUI_->connectToFeeder())
            {
                connectionEstablished_ = true;
                
                auto notification = CommunicationStatusNotification(communicationManagerUI_->getCurrentState(), communicationManagerUI_->getProcessNumber());
                sendMessageToMainProcess(notification.getFrameBytes());
            }
        }
    }
    else
    {
        connectionEstablishingInterrupt_.stop();
    }
}

void ProcessManager::stopCommunication()
{
    runCommunicationProcess_ = false;
}

void ProcessManager::startCommunication()
{
    unsigned int priority;
    message_queue::size_type receivedSize;

    while(runCommunicationProcess_)
    {
        try
        {
            vector<uint8_t> packet(uiMessageQueuesParameters_.messageSize);
            receivingMessageQueue_->receive(packet.data(), packet.size(), receivedSize, priority);

            packet.resize(receivedSize);
            packet.shrink_to_fit();

            handleMessageQueue(packet);
        }
        catch(interprocess_exception &ex)
        {
            if ( logger_.isErrorEnable())
            {
                const string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Receiving data ::" + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ProcessManager::handleMessageQueue(const vector<uint8_t> &data)
{
    const auto command = uiCommandFactory_.createCommand(data);

    command->accept(*(mainProcessHandlerVisitor_.get()));
}


void ProcessManager::sendMessageToMainProcess(const vector<uint8_t> &data)
{
    sendingMessageQueue_->send(data.data(), data.size(), 0);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("ProcessManager:: Process - ") + to_string(processNumber_) + ". Send msg to main process.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
