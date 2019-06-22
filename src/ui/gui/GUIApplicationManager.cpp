#include <config_reader/ConfigurationReader.h>
#include "GUIApplicationManager.h"
#include "MainWindow.h"

#include <interfaces/hm/HMRegisterNotification.h>
#include <interfaces/hm/HMHeartbeatNotification.h>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/creation_tags.hpp>

using namespace gui;
using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

GUIApplicationManager::GUIApplicationManager(std::shared_ptr<MainWindow> mainWindow)
    : mainWindow_(mainWindow),
      uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
      uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH)),
      runCommunicationThread_(false),
      logger_(Logger::getInstance()),
      WELCOME_PAGE_DURATION_MS(3000)
{
    interprocessCommandVisitor_ = make_shared<GUIInterprocessCommandVisitor>(mainWindow);
}

GUIApplicationManager::~GUIApplicationManager()
{
    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-GUI- UIApplicationManager :: Destructor.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }
    stopGUI();
    timerInterrupt_.stop();
}

bool GUIApplicationManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeGUIMessageQueue();
    isSuccess = isSuccess & initializeSharedMemory();

    initializeHMMessageQueue();
    initializeHM();

    return isSuccess;
}

bool GUIApplicationManager::initializeGUIMessageQueue()
{
    try
    {
        communicationMessageQueue_ = make_unique<MessageQueueWrapper>(uiMessageQueuesParameters_.guiProcessQueueName, uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-GUI-ApplicationManager:: ") + " During openning main queue - " + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("-GUI- ApplicationManager:: ") + " GUI massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool GUIApplicationManager::initializeSharedMemory()
{
    try
    {
        sharedMemory_ = make_unique<SharedMemoryWrapper>(uiSharedMemoryParameters_.sharedMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-GUI- ApplicationManager :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
}

bool GUIApplicationManager::initializeHMMessageQueue()
{
    try
    {
        hmMessageQueue_ = make_shared<MessageQueueWrapper>(uiMessageQueuesParameters_.hmQueueName, uiMessageQueuesParameters_.messageSize);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: ") + uiMessageQueuesParameters_.hmQueueName + (" queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: Main message queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool GUIApplicationManager::initializeHM()
{
    if (!hmMessageQueue_)
        return true;

    HMRegisterNotification notification(HMNodes::GUI);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-GUI- UIApplicationManager :: Init timer.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }

    timerInterrupt_.startPeriodic(HM_INTERVAL_MS, this);

    return true;
}

void GUIApplicationManager::interruptNotification(timer_t timerID)
{
    HMHeartbeatNotification notification(HMNodes::GUI);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);
}

void GUIApplicationManager::startGUI()
{
    runCommunicationThread_ = true;
    interprocessCommunicationThread_ = thread(&GUIApplicationManager::interprocessCommunication, this);

    mainWindow_->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    mainWindow_->show();
}

void GUIApplicationManager::stopGUI()
{
    if(interprocessCommunicationThread_.joinable())
    {
        runCommunicationThread_ = false;
        interprocessCommunicationThread_.join();
    }
}

void GUIApplicationManager::interprocessCommunication()
{
    while(runCommunicationThread_)
    {
        try
        {
            const auto packet = communicationMessageQueue_->receive();
            handleCommand(packet);
        }
        catch(interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-GUI- ApplicationManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

    }
}

void GUIApplicationManager::handleCommand(const std::vector<uint8_t>& packet)
{
    const auto interfaceType = static_cast<InterfaceType>(packet[Frame::INTERFACE_TYPE]);

    if(interfaceType == InterfaceType::GUI)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::COMMAND)
        {
            const auto command = commandFactory_.createCommand(packet);
            command->accept(*(interprocessCommandVisitor_.get()));
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-GUI- ApplicationManager :: Received wrong type of message.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-GUI- ApplicationManager :: Received wrong type of interface.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}
