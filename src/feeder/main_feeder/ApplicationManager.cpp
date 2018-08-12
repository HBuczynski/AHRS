#include "ApplicationManager.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;

ApplicationManager::ApplicationManager()
    :   sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
        messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
        executableFilesNames_(ConfigurationReader::getFeederExecutableFiles(FEEDER_PARAMETERS_FILE_PATH)),
        logger_(Logger::getInstance())
{}

ApplicationManager::~ApplicationManager()
{}

bool ApplicationManager::initialize()
{
    bool isSuccess = true;

    isSuccess &= initializeMainQueue();
    isSuccess &= initializeExternalQueue();
    isSuccess &= initializeInternalQueue();

    isSuccess &= initializeExternalSharedMemory();
    isSuccess &= initializeInternalSharedMemory();

    isSuccess &= createExternalCommunicationProcess();
    isSuccess &= createInternalCommunicationProcess();

    return isSuccess;
}

bool ApplicationManager::initializeMainQueue()
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
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

bool ApplicationManager::initializeExternalQueue()
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
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

bool ApplicationManager::initializeInternalQueue()
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
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

bool ApplicationManager::initializeExternalSharedMemory()
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
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("ApplicationManager ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        return false;
    }

    return true;
}

bool ApplicationManager::initializeInternalSharedMemory()
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

        return false;
    }

    return true;
}

bool ApplicationManager::createExternalCommunicationProcess()
{
    char *firstArg1 = const_cast<char*>(executableFilesNames_.externalCommunication.c_str());
    char *arguments[] = {firstArg1, NULL};

    int status;
    int out[2];

    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);
    pipe(out);
    posix_spawn_file_actions_adddup2(&action, out[1], STDOUT_FILENO);
    posix_spawn_file_actions_addclose(&action, out[0]);

    status = posix_spawn(&externalProcess_, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("ApplicationManager :: External process was initialized, process ID: ") + to_string(externalProcess_);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return true;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ApplicationManager :: External process was not initialized correctly, process ID: ") + to_string(externalProcess_);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
}

bool ApplicationManager::createInternalCommunicationProcess()
{
    char *firstArg1 = const_cast<char*>(executableFilesNames_.internalCommunication.c_str());
    char *arguments[] = {firstArg1, NULL};

    int status;
    int out[2];

    // This attribute is responsible for file descriptors.
    posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init(&action);
    pipe(out);
    posix_spawn_file_actions_adddup2(&action, out[1], STDOUT_FILENO);
    posix_spawn_file_actions_addclose(&action, out[0]);

    status = posix_spawn(&internalProcess_, arguments[0], &action, NULL, arguments, environ);

    if(status == 0)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("ApplicationManager :: Internal process was initialized, process ID: ") + to_string(internalProcess_);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        return true;
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("ApplicationManager :: Internal process was not initialized correctly, process ID: ") + to_string(internalProcess_);
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }
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