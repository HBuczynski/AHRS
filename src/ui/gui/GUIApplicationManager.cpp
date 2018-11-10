#include <config_reader/ConfigurationReader.h>
#include "GUIApplicationManager.h"
#include "MainWindow.h"

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
    stopGUI();
}

bool GUIApplicationManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeGUIMessageQueue();
    isSuccess = isSuccess & initializeSharedMemory();

    return isSuccess;
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
            const string message = string("GUIApplicationManager:: ") + " During openning main queue - " + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("GUIApplicationManager:: ") + " GUI massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool GUIApplicationManager::initializeSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        sharedMemoryMutex_ = make_unique<named_mutex>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str());
        // Creating shared memory.
        sharedMemory_ = make_unique<shared_memory_object>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str(), read_write);
        // Mapped shared memory.
        mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("GUIApplicationManager :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    return true;
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
                const string message = string("ProcessManager :: ") + ex.what();
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
                const string message = string("GUIApplicationManager :: Received wrong type of message.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("GUIApplicationManager :: Received wrong type of interface.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}