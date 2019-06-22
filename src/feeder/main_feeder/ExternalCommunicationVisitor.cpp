#include "ExternalCommunicationVisitor.h"
#include "ApplicationManager.h"

#include "machine_state/CalibrationState.h"
#include "machine_state/MainAcqState.h"
#include "machine_state/PerformBitState.h"
#include <interfaces/wireless_commands/CommandFactory.h>
#include <interfaces/wireless_commands/CalibrateAccelerometerCommand.h>
#include <interfaces/wireless_commands/CallibrateMagnetometerCommand.h>
#include <interfaces/wireless_commands/SetPlaneCommand.h>
#include <interfaces/wireless_responses/FeederStateCodeResponse.h>

#include <config_reader/ConfigurationReader.h>

using namespace std;
using namespace config;
using namespace main_process;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;

ExternalCommunicationVisitor::ExternalCommunicationVisitor()
    : sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
{}

ExternalCommunicationVisitor::~ExternalCommunicationVisitor()
{}

void ExternalCommunicationVisitor::registerApplicationManager(ApplicationManager *appManager)
{
    appManager_ = appManager;
    initializeSharedMemory();
}

void ExternalCommunicationVisitor::initializeSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-EXTCOMM- CommandHandlerVisitor:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOMM- CommandHandlerVisitor :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ExternalCommunicationVisitor::visit(const CalibrateMgnDemandCommand &command)
{

}

void ExternalCommunicationVisitor::visit(const FeederWirelessWrapperCommand& command)
{
    const auto frame = command.getDataFrame();

    CommandFactory commandFactory;
    auto newCommand = commandFactory.createCommand(frame);

    switch (newCommand->getCommandType())
    {
        case CommandType::CALIBRATE_ACCELEROMETER :
        {
            if (appManager_->getCurrentStateName() == "CalibrationState")
            {
                auto state = appManager_->getState("CalibrationState");
                auto calibrateCommand = static_pointer_cast<CalibrateAccelerometerCommand, Command>(commandFactory.createCommand(frame));
                static_pointer_cast<CalibrationState, hsm::State>(state)->accelerometerAction(calibrateCommand->getAxis(), calibrateCommand->getAction());
            }
            break;
        }
        case CommandType::CALIBRATE_MAGNETOMETER :
        {
            if (appManager_->getCurrentStateName() == "CalibrationState")
            {
                auto state = appManager_->getState("CalibrationState");
                static_pointer_cast<CalibrationState, hsm::State>(state)->approveMagnetometer();
            }
            break;
        }
        case CommandType::SET_PLANE_NAME :
        {
            auto setPlaneNameCommand = static_pointer_cast<SetPlaneCommand, Command>(commandFactory.createCommand(frame));
            appManager_->getFeederDataContainer().planeName = setPlaneNameCommand->getPlaneName();

            break;
        }
        default:
            break;
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor :: Received - FeederWirelessWrapperCommand.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ExternalCommunicationVisitor::visit(const communication::FeederCodeDemandCommand& command)
{
    FeederStateCodeResponse codeCommand(getCode());
    auto packet = codeCommand.getFrameBytes();
    externalSharedMemory_->write(packet);
}

void ExternalCommunicationVisitor::visit(const CalibrationStatusNotification &command)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor :: Received - CalibrationStatusNotification");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ExternalCommunicationVisitor::visit(const communication::StateNotification& command)
{
    const auto type = static_cast<FeederStateCode>(command.getStateCode());

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor :: Received - StateNotification - ")
                + to_string(static_cast<int>(command.getStateCode()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    switch (type)
    {
        case FeederStateCode::REGISTERED_USERS :
            appManager_->handleEvent("RUN_REGISTARTION");
            break;

        case FeederStateCode::SETTINNG :
            appManager_->handleEvent("GET_SETTINGS");
            break;

        case FeederStateCode::CALLIBATION :
            appManager_->handleEvent("RUN_CALLIBRATION");
            break;

        case FeederStateCode::PERFORM_BIT :
            appManager_->handleEvent("CHECK_BIT");
            break;

        case FeederStateCode::MAIN_ACQ :
        {
            auto currentName = appManager_->getCurrentStateName();

            if(currentName == string("MainAcqState"))
                appManager_->handleEvent("RELAUNCH_ACQ");
            else
                appManager_->handleEvent("START_MAIN_ACQ");

            break;
        }
        case FeederStateCode::STOP_ACQ :
        {
            auto currentName = appManager_->getCurrentStateName();
            if(currentName == string("MainAcqState"))
            {
                auto state = appManager_->getState("MainAcqState");
                static_pointer_cast<MainAcqState, hsm::State>(state)->stopAcq();
            }
        }
        default:
            break;
    }
}

void ExternalCommunicationVisitor::visit(const communication::DbHashNotification& command)
{
    appManager_->setHash(command.getHash());

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor :: Received - DbHashNotification - Hash: ")
                + to_string(command.getHash());
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void ExternalCommunicationVisitor::visit(const communication::UDPBitsNotification& command)
{
    auto currentName = appManager_->getCurrentStateName();
    if(currentName == string("PerformBitState"))
    {
        auto state = appManager_->getState("PerformBitState");
        static_pointer_cast<PerformBitState, hsm::State>(state)->approveUDPBits();
    }
}

FeederStateCode ExternalCommunicationVisitor::getCode()
{
    const auto name = appManager_->getCurrentStateName();

    if ( name == "Idle")
        return FeederStateCode::IDLE;
    else if ( name == "CalibrationState")
        return FeederStateCode::CALLIBATION;
    else if ( name == "ConnectionState")
        return FeederStateCode::CONNECTION;
    else if ( name == "MainAcqState")
        return FeederStateCode::MAIN_ACQ;
    else if ( name == "MainErrorState")
        return FeederStateCode::ERROR;
    else if ( name == "MainFaultManagementState")
        return FeederStateCode::FAULT_MANAGEMENT;
    else if ( name == "PerformBitState")
        return FeederStateCode::PERFORM_BIT;
    else if ( name == "RedundantAcqState")
        return FeederStateCode::REDUNDANT_ACQ;
    else if ( name == "RegisterUserState")
        return FeederStateCode::REGISTERED_USERS;
    else if ( name == "SettingsState")
        return FeederStateCode::SETTINNG;
}
