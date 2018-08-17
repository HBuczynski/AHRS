#include <unistd.h>
#include "UIApplicationManager.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace utility;
using namespace config;
using namespace main_process;
using namespace boost::interprocess;

UIApplicationManager::UIApplicationManager()
    : uiWirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH.c_str())),
      uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
      uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH.c_str())),
      uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH.c_str())),
      runSystem_(true),
      logger_(Logger::getInstance())
{}

UIApplicationManager::~UIApplicationManager()
{
    // Removing message queues.
    message_queue::remove(uiMessageQueuesParameters_.firstCommunicationQueueName.c_str());
    message_queue::remove(uiMessageQueuesParameters_.secondCommunicationQueueName.c_str());
    message_queue::remove(uiMessageQueuesParameters_.mainProcessQueueName.c_str());

    // Removing shared memory.
    named_mutex::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
    shared_memory_object::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
}

bool UIApplicationManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeMainProcessMessageQueue();
    isSuccess = isSuccess & initializeGUIMessageQueue();
    isSuccess = isSuccess & initializeSharedMemory();
    isSuccess = isSuccess & communicationProcessesHandler_.initialize();

    return isSuccess;
}

bool UIApplicationManager::initializeMainProcessMessageQueue()
{
    try
    {
        message_queue::remove(uiMessageQueuesParameters_.mainProcessQueueName.c_str());
        mainMessageQueue = make_shared<message_queue>(create_only, uiMessageQueuesParameters_.mainProcessQueueName.c_str(),
                uiMessageQueuesParameters_.messageQueueNumber,
                uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("UIApplicationManager:: Main message queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager:: Main message queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool UIApplicationManager::initializeGUIMessageQueue()
{
    try
    {
        message_queue::remove(uiMessageQueuesParameters_.guiProcessQueueName.c_str());
        guiCommunicationMessageQueue = make_shared<message_queue>(create_only, uiMessageQueuesParameters_.guiProcessQueueName.c_str(),
                uiMessageQueuesParameters_.messageQueueNumber,
                uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("UIApplicationManager:: Gui message queue has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager:: Gui message queue has initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool UIApplicationManager::initializeSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        named_mutex::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
        sharedMemoryMutex_ = make_unique<named_mutex>(create_only, uiSharedMemoryParameters_.sharedMemoryName.c_str());

        // Creating shared memory.
        shared_memory_object::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
        sharedMemory_ = make_unique<shared_memory_object>(create_only, uiSharedMemoryParameters_.sharedMemoryName.c_str(), read_write);

        // Resize shared memory.
        sharedMemory_->truncate(uiSharedMemoryParameters_.sharedMemorySize);
        mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("UIApplicationManager:: Shared Memory has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("UIApplicationManager:: Shared Memory has initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

void UIApplicationManager::startUISystem()
{
    while (runSystem_)
    {

    }
}

void UIApplicationManager::stopUISystem()
{
    runSystem_ = false;
}