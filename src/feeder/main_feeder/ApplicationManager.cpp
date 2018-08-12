#include "ApplicationManager.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

ApplicationManager::ApplicationManager()
    :   sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
        messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
        logger_(Logger::getInstance())
{}

ApplicationManager::~ApplicationManager()
{}

void ApplicationManager::initialize()
{
    initializeMainQueue();
    initializeExternalQueue();
    initializeInternalQueue();

    initializeExternalSharedMemory();
    initializeInternalSharedMemory();

    createExternalCommunicationProcess();
    createInternalCommunicationProcess();
}

void ApplicationManager::initializeMainQueue()
{
    try
    {
        message_queue::remove(messageQueuesParameters_.mainProcessQueueName.c_str());
        mainComMessageQueue = make_shared<message_queue>(create_only, messageQueuesParameters_.mainProcessQueueName.c_str(),
                messageQueuesParameters_.messageQueueNumber,
                messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ApplicationManager::initializeExternalQueue()
{
    try
    {
        message_queue::remove(messageQueuesParameters_.externalCommunicationQueueName.c_str());
        externalComMessageQueue = make_shared<message_queue>(create_only, messageQueuesParameters_.externalCommunicationQueueName.c_str(),
                                                            messageQueuesParameters_.messageQueueNumber,
                                                            messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ApplicationManager::initializeInternalQueue()
{
    try
    {
        message_queue::remove(messageQueuesParameters_.internalCommunicationQueueName.c_str());
        internalComMessageQueue = make_shared<message_queue>(create_only, messageQueuesParameters_.internalCommunicationQueueName.c_str(),
                messageQueuesParameters_.messageQueueNumber,
                messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ApplicationManager::initializeExternalSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        named_mutex::remove(sharedMemoryParameters_.externalMemoryName.c_str());
        externalSharedMemoryMutex_ = std::make_unique<named_mutex>(open_only, sharedMemoryParameters_.externalMemoryName.c_str());

        // Creating shared memory.
        shared_memory_object::remove(sharedMemoryParameters_.externalMemoryName.c_str());
        externalSharedMemory_ = std::make_unique<shared_memory_object>(open_only, sharedMemoryParameters_.externalMemoryName.c_str(), read_write);

        // Resize shared memory.
        externalSharedMemory_->truncate(sharedMemoryParameters_.sharedMemorySize);
        externalMappedMemoryRegion_ = std::make_unique<mapped_region>(*externalSharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ApplicationManager::initializeInternalSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        named_mutex::remove(sharedMemoryParameters_.internalMemoryName.c_str());
        internalSharedMemoryMutex_ = std::make_unique<named_mutex>(open_only, sharedMemoryParameters_.internalMemoryName.c_str());

        // Creating shared memory.
        shared_memory_object::remove(sharedMemoryParameters_.internalMemoryName.c_str());
        internalSharedMemory_ = std::make_unique<shared_memory_object>(open_only, sharedMemoryParameters_.internalMemoryName.c_str(), read_write);

        // Resize shared memory.
        internalSharedMemory_->truncate(sharedMemoryParameters_.sharedMemorySize);
        internalMappedMemoryRegion_ = std::make_unique<mapped_region>(*internalSharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable()) {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ApplicationManager::createExternalCommunicationProcess()
{

}

void ApplicationManager::createInternalCommunicationProcess()
{

}

void ApplicationManager::launchFeederSystem()
{
    processingThread_ = thread(&ApplicationManager::runProcessing, this);

    if(processingThread_.joinable())
    {
        processingThread_.join();
    }
}

void ApplicationManager::runProcessing()
{
    unsigned int priority;
    message_queue::size_type receivedSize;

    while(true)
    {
        try
        {
            vector<uint8_t> packet(messageQueuesParameters_.messageSize);
            mainComMessageQueue->receive(packet.data(), packet.size(), receivedSize, priority);

            packet.resize(receivedSize);
            packet.shrink_to_fit();

            handleCommand(packet);
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

void ApplicationManager::handleCommand(const std::vector<uint8_t>& packet)
{
    const auto interfaceType = static_cast<InterfaceType>(packet[Frame::INTERFACE_TYPE]);

    if(interfaceType == InterfaceType::COMMUNICATION_PROCESS_FEEDER)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::COMMAND)
        {
            const auto command = externalCommandFactory_.createCommand(packet);
            command->accept(externalVisitor_);
        }
        else if (frameType == FrameType::NOTIFICATION)
        {
            const auto notification = externalNotificationFactory_.createNotification(packet);
            notification->accept(externalVisitor_);
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
    else if (interfaceType == InterfaceType::ETHERNET_FEEDER)
    {
        //TODO
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