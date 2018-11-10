#include <unistd.h>
#include "UIApplicationManager.h"
#include <interfaces/gui/GUIWindowCommand.h>
#include <interfaces/gui/GUIInformationWindowCommand.h>
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
      externalCommunicationVisitor_(make_unique<ExternalCommInterprocessVisitor>(this)),
      guiInterprocessVisitor_(make_unique<GUIInterprocessVisitor>(this)),
      runSystem_(true),
      logger_(Logger::getInstance())
{}

UIApplicationManager::~UIApplicationManager()
{
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
        mainMessageQueue_ = make_shared<MessageQueueWrapper>(uiMessageQueuesParameters_.mainProcessQueueName,
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
        sharedMemory_ = make_unique<SharedMemoryWrapper>(uiSharedMemoryParameters_.sharedMemoryName, uiSharedMemoryParameters_.sharedMemorySize);
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

    while(runSystem_)
    {
        try
        {
            const auto packet = mainMessageQueue_->receive();
            handleMessage(packet);
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

void UIApplicationManager::handleMessage(const std::vector<uint8_t> &packet)
{
    const auto interfaceType = static_cast<InterfaceType>(packet[Frame::INTERFACE_TYPE]);

    if(interfaceType == InterfaceType::GUI)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::RESPONSE)
        {
            const auto response = guiResponseFactory_.createCommand(packet);
            response->accept(*(guiInterprocessVisitor_.get()));
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("UIApplicationManager :: Received wrong type of GUI's message");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else if (interfaceType == InterfaceType::COMMUNICATION_PROCESS_UI)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::NOTIFICATION)
        {
            const auto notification = uiNotificationFactory_.createCommand(packet);
            notification->accept(*(externalCommunicationVisitor_.get()));
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("UIApplicationManager :: Received wrong type of COMMUNICATION_PROCESS_UI's message.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("UIApplicationManager :: Received wrong type of interface.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void UIApplicationManager::stopUISystem()
{
    runSystem_ = false;
}

void UIApplicationManager::setWelcomePage()
{
    auto command = GUIWindowCommand(PagesType::WELCOME_PAGE);
    auto packet = command.getFrameBytes();
    guiProcessHandler_.sendMessage(packet);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager :: Send") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UIApplicationManager::communicationInProgress()
{
    auto command = GUIWindowCommand(PagesType::CONNECTING_PAGE);
    auto packet = command.getFrameBytes();
    guiProcessHandler_.sendMessage(packet);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager :: Send") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UIApplicationManager::setInformationPage(uint8_t master, uint8_t redundant, uint8_t bitMaster, uint8_t bitRedundant)
{
    auto command = GUIInformationWindowCommand(master, redundant, bitMaster, bitRedundant);
    auto packet = command.getFrameBytes();
    guiProcessHandler_.sendMessage(packet);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UIApplicationManager :: Send") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UIApplicationManager::sendToExternalCommunicationProcess(vector<uint8_t> data, UICommunicationMode mode)
{
    communicationProcessesHandler_.sendMessage(data, mode);
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

