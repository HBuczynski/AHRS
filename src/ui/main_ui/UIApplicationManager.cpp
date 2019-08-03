#include "UIApplicationManager.h"

#include <functional>
#include <utility/Utility.h>
#include <common/HMNodes.h>
#include <hal/include/RPIParams.h>
#include <interfaces/gui/GUIBITSCommand.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <interfaces/gui/GUIWindowCommand.h>

#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>
#include <interfaces/wireless_measurement_commands/FeederData.h>
#include <interfaces/hm/HMRegisterMainNotification.h>
#include <interfaces/hm/HMHeartbeatNotification.h>
#include <interfaces/fm/FMCommandFactory.h>

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
      hmVisitor_(make_unique<HMVisitor>(this)),
      runSystem_(true),
      timerInterrupt_("MainUI"),
      logger_(Logger::getInstance())
{}

UIApplicationManager::~UIApplicationManager()
{
    named_mutex::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
    shared_memory_object::remove(uiSharedMemoryParameters_.sharedMemoryName.c_str());
    timerInterrupt_.stop();
}

bool UIApplicationManager::initialize()
{
    bool isSuccess = true;
    isSuccess = isSuccess & initializeMainProcessMessageQueue();
    isSuccess = isSuccess & initializeSharedMemory();
    isSuccess = isSuccess & initializeDb();
    isSuccess = isSuccess & communicationProcessesHandler_.initialize();
    isSuccess = isSuccess & guiProcessHandler_.initialize();

    initializeHMMessageQueue();
    initializeHM();

    hmVisitor_->initialize();
    fmVisitor_.initializeCommunicationProcess(&communicationProcessesHandler_);
    fmVisitor_.initializeGuiProcess(&guiProcessHandler_);

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

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: Main message queue has been initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
    }

    return true;
}

bool UIApplicationManager::initializeHMMessageQueue()
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

    if (logger_.isDebugEnable())
    {
        const std::string message = std::string("-MAIN- UIApplicationManager:: Main message queue has been initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
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

    if(logger_.isDebugEnable())
    {
        const string message = string("-MAIN- UIApplicationManager:: Shared Memory has initialized correctly.");
        logger_.writeLog(LogType::DEBUG_LOG, message);
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

//    runDbThread_ = true;
//    dbThread_ = thread(&UIApplicationManager::saveGeneral2DB, this);

    return isSuccess;
}

bool UIApplicationManager::initializeHM()
{
    if (!hmMessageQueue_)
        return true;

    HMRegisterMainNotification notification(HMNodes::MAIN_UI, uiMessageQueuesParameters_.mainProcessQueueName, uiMessageQueuesParameters_.messageSize);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);
    timerInterrupt_.startPeriodic(HM_INTERVAL_MS, this);

    return true;
}

void UIApplicationManager::interruptNotification(timer_t timerID)
{
    HMHeartbeatNotification notification(HMNodes::MAIN_UI);

    auto packet = notification.getFrameBytes();
    hmMessageQueue_->send(packet);
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

            if (!packet.empty())
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

        this_thread::sleep_for(std::chrono::milliseconds(10));
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
    else if (interfaceType == InterfaceType::HM)
    {
        const auto frameType = static_cast<FrameType>(packet[Frame::FRAME_TYPE]);

        if(frameType == FrameType::COMMAND)
        {
            auto command = hmCommandFactory_.createCommand(packet);
            command->accept(*(hmVisitor_.get()));
        }
        else
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("UIApplicationManager :: Received wrong type of HM's message.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
    else if (interfaceType == InterfaceType::FM)
    {
        FMCommandFactory fmCommandFactory;

        auto command = fmCommandFactory.createCommand(packet);
        command->accept(fmVisitor_);
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
    runDbThread_ = false;

    if(dbThread_.joinable())
        dbThread_.join();

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

void UIApplicationManager::saveGeneral2DB()
{
    CockpitProperties properties = {0};
    CockpitNetwork network = {0};
    RPIParams params;

    while(runDbThread_)
    {
        auto cores = utility::Utility::getCPU(400);

        properties.core1 = cores[0] * 100.f;
        properties.core2 = cores[1] * 100.f;
        properties.core3 = cores[2] * 100.f;
        properties.core4 = cores[3] * 100.f;

        properties.temperature = params.getTemp();

        network.bandwith = 2.4;
        network.networkMode = 1;
        network.networkNumber = 1;

        network.timestamp = properties.timestamp = TimeManager::getImeSinceEpoch();

        cockpitDb_->insertCockpitNetwork(network);
        cockpitDb_->insertCockpitProperties(properties);

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

std::string UIApplicationManager::getPlaneName() const
{
    return planeName_;
}

void UIApplicationManager::setPlaneName(const std::string &planeName)
{
    planeName_ = planeName;
}

void UIApplicationManager::saveMeasurements2DB()
{
    runSavingMeasurements_ = true;

    while (runSavingMeasurements_)
    {
        communication::MeasuringDataFactory dataFactory_;

        try
        {
            const auto frame = sharedMemory_->read();

            if(frame.size() != 0)
            {
                auto flightData = static_pointer_cast<communication::FeederData, communication::MeasuringData>(
                        dataFactory_.createCommand(frame));

                const auto measurements = flightData->getMeasurements();
                cockpitDb_->insertFlightMeasurement(measurements.flightMeasurements);
            }
        }
        catch (exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-MAIN- UIApplicationManager :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void UIApplicationManager::stopMeasurements2DB()
{
    runSavingMeasurements_ = false;

    if(dbMeasurementThread_.joinable())
        dbMeasurementThread_.join();
}
