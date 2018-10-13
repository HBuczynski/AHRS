#include <unistd.h>
#include "UIApplicationManager.h"
#include <interfaces/gui/GUIWindowCommand.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>

#include "machine_state/UIIdleState.h"
#include "ui/main_ui/machine_state/UIWelcomeState.h"

using namespace std;
using namespace utility;
using namespace config;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

UIApplicationManager::UIApplicationManager()
    : uiWirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH.c_str())),
      uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
      uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH.c_str())),
      uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH.c_str())),
      currentState_(make_unique<UIIdleState>()),
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
    isSuccess = isSuccess & initializeSharedMemory();
    isSuccess = isSuccess & communicationProcessesHandler_.initialize();
    isSuccess = isSuccess & guiProcessHandler_.initialize();

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
    setNewState(new UIWelcomeState);
    currentState_->setWelcomePage(*this);

    while (runSystem_)
    {
        //TODO: Add command handlers.
    }
}

void UIApplicationManager::stopUISystem()
{
    runSystem_ = false;
}

void UIApplicationManager::setWelcomePage()
{
    auto command = GUIWindowCommand(WindowType::WELCOME_PAGE);
    guiProcessHandler_.sendMessage(command.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager :: Send") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UIApplicationManager::communicationInProgress()
{
    auto command = GUIWindowCommand(WindowType::CONNECTION_ESTABLISHING);
    guiProcessHandler_.sendMessage(command.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager :: Send") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UIApplicationManager::setNewState(UIAbstractState *newState)
{
    if(newState != nullptr)
    {
        currentState_.reset(newState);

        if(logger_.isInformationEnable())
        {
            const string message = string("UIApplicationManager :: Change state: " + newState->getName());
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isWarningEnable())
        {
            const string message = string("UIApplicationManager :: Empty state has been forwarded to the state machine.");
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
    }
}
