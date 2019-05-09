#include "UIApplicationManager.h"

#include <functional>
#include <interfaces/gui/GUIBITSCommand.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <interfaces/gui/GUIWindowCommand.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace main_process;
using namespace communication;
using namespace boost::interprocess;

UIApplicationManager::UIApplicationManager(const string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
    : HSM(name, transitionTable, rootState),
      uiWirelessCommunicationParameters_(config::ConfigurationReader::getUIWirelessCommunication(UI_PARAMETERS_FILE_PATH.c_str())),
      uiMessageQueuesParameters_(config::ConfigurationReader::getUIMessageQueues(UI_PARAMETERS_FILE_PATH.c_str())),
      uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH.c_str())),
      uiCommunicationSystemParameters_(config::ConfigurationReader::getUICommunicationProcessSystemParameters(UI_COMMUNICATION_PROCESS_PARAMETERS_PATH.c_str())),
      externalCommunicationVisitor_(make_unique<ExternalCommInterprocessVisitor>(this)),
      guiInterprocessVisitor_(make_unique<GUIInterprocessVisitor>(this)),
      runSystem_(true),
      logger_(Logger::getInstance())
{}

UIApplicationManager::~UIApplicationManager()
{
    named_mutex::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
    shared_memory_object::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
}

bool UIApplicationManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeMainProcessMessageQueue();
    isSuccess = isSuccess & initializeSharedMemory();
    isSuccess = isSuccess & initializeDb();
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
            const string message = string("-MAIN- UIApplicationManager:: Main message queue has not been initialized correctly - ") + ex.what();
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
            const string message = string("-MAIN- UIApplicationManager:: Shared Memory has not initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- UIApplicationManager:: Shared Memory has initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool UIApplicationManager::initializeDb()
{
    bool isSuccess = true;
    std::hash<std::string> hasher;

    const auto dbName = string("CockpitDB_") + TimeManager::getTimeAndDate() + string(".db");
    cockpitDb_ = make_shared<database::CockpitDb>(dbName);

    isSuccess = isSuccess & cockpitDb_->openDb();
    isSuccess = isSuccess & cockpitDb_->createTable();

    if(isSuccess)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: Database has initialized correctly.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-MAIN- UIApplicationManager:: Database has not initialized correctly - ");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
        return false;
    }

    uint32_t hashed = hasher(dbName);
    cockpitDb_->insertHASH(hashed);

    return isSuccess;
}

uint32_t UIApplicationManager::getDbHash() const noexcept
{
    return cockpitDb_->getHash();
}

const string& UIApplicationManager::getDbName() const noexcept
{
    return cockpitDb_->getName();
}

void UIApplicationManager::startUISystem()
{
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

void UIApplicationManager::sendToGUIProcess(vector<uint8_t> data)
{
    guiProcessHandler_.sendMessage(data);
}

void UIApplicationManager::sendToExternalCommunicationProcess(vector<uint8_t> data, UICommunicationMode mode)
{
    communicationProcessesHandler_.sendMessage(data, mode);
}
