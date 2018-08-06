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
        sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
        messageQueuesParameters_(ConfigurationReader::getFeederMessageQueues(FEEDER_PARAMETERS_FILE_PATH)),
        feederType_(ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH)),
        logger_(Logger::getInstance())
{
    initializeMessageQueueCommunication();
    initializeSharedMemoryCommunication();
    initializeExternalCommmunication();
}

ProcessManager::~ProcessManager()
{

}

void ProcessManager::initializeExternalCommmunication()
{
    clientUDPManager_ = make_shared<ClientUDPManager>();

    switch (feederType_.processNumber)
    {
        case 1 :
        {
            server_ = make_shared<ServerTCP>(feederExternalWirelessParameters_.firstPort, feederExternalWirelessParameters_.maxUserNumber, clientUDPManager_);
            break;
        }
        case 2 :
        {
            server_ = make_shared<ServerTCP>(feederExternalWirelessParameters_.secondPort, feederExternalWirelessParameters_.maxUserNumber, clientUDPManager_);
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
        messageQueue = make_shared<message_queue>(create_only,
                                                  messageQueuesParameters_.externalCommunicationQueueName.c_str(),
                                                  messageQueuesParameters_.messageQueueNumber,
                                                  messageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("External Communication :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ProcessManager::initializeSharedMemoryCommunication()
{
    try
    {
        // Creating shared memory's mutex.
        named_mutex::remove(sharedMemoryParameters_.externalMemoryName.c_str());
        sharedMemoryMutex_ = make_unique<named_mutex>(create_only, sharedMemoryParameters_.externalMemoryName.c_str());

        // Creating shared memory.
        shared_memory_object::remove(sharedMemoryParameters_.externalMemoryName.c_str());
        sharedMemory_ = make_unique<shared_memory_object>(create_only, sharedMemoryParameters_.externalMemoryName.c_str(), read_write);

        // Resize shared memory.
        sharedMemory_->truncate(sharedMemoryParameters_.sharedMemorySize);
        mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("External Communication ::") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void ProcessManager::runProcessConfiguration()
{
    server_->startUserActivation();
}




