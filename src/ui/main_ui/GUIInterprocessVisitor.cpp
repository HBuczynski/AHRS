#include "GUIInterprocessVisitor.h"

#include <config_reader/UIParameters.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>
#include <interfaces/wireless_commands/StartAcquisitionCommand.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_commands/SetPlaneCommand.h>
#include <interfaces/wireless_commands/CalibrateDataCommand.h>
#include <interfaces/wireless_commands/ShutdownCommand.h>
#include <interfaces/wireless_commands/RestartCommand.h>

#include "UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

GUIInterprocessVisitor::GUIInterprocessVisitor(UIApplicationManager *uiApplicationManager)
    : uiApplicationManager_(uiApplicationManager),
      logger_(Logger::getInstance())
{}

GUIInterprocessVisitor::~GUIInterprocessVisitor()
{}

void GUIInterprocessVisitor::visit(GUIPlaneResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-GUIInterprocessVisitor:: Received - ") + data.getName() + " - plane: "
                + data.getPlane();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    uiApplicationManager_->setPlaneName(data.getPlane());

    auto planeCommand = SetPlaneCommand(data.getPlane());
    auto commandWrapper = SendingDataCommand(planeCommand.getFrameBytes());
    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), data.getMode());

    this_thread::sleep_for(std::chrono::milliseconds(100));

    CalibrateDataCommand calibrateDataCommand;
    auto commandWrapper2 = SendingDataCommand(calibrateDataCommand.getFrameBytes());
    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper2.getFrameBytes(), data.getMode());
}

void GUIInterprocessVisitor::visit(communication::GUIWindowResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-GUIInterprocessVisitor:: Received - ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    switch (data.getPageType())
    {
    case PagesType::CALLIBRATION_PAGE :
        uiApplicationManager_->handleEvent("CALIBRATE");
        break;

    case PagesType::BITS_PAGE :
        uiApplicationManager_->handleEvent("PERFORM_BIT");
        break;

    case PagesType::AHRS_PAGE :
        uiApplicationManager_->handleEvent("DATA_ACQUISITION");
        break;

    default:
        break;
    }
}

void GUIInterprocessVisitor::visit(communication::GUIWirelessComWrapperResponse& data)
{
    auto commandWrapper = SendingDataCommand(data.getDataFrame());
    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), data.getMode());

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-GUIInterprocessVisitor:: Received - ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void GUIInterprocessVisitor::visit(GUIStartAcqResponse& data)
{
//    uiApplicationManager_->saveMeasurements2DB();
}

void GUIInterprocessVisitor::visit(GUIStopAcqResponse& data)
{
    uiApplicationManager_->stopMeasurements2DB();
}

void GUIInterprocessVisitor::visit(communication::GUIRestartResponse& data)
{
    auto command = RestartCommand();
    auto commandWrapper = SendingDataCommand(command.getFrameBytes());
    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);

    this_thread::sleep_for(std::chrono::milliseconds(100));

    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::REDUNDANT);

    this_thread::sleep_for(std::chrono::milliseconds(800));

    system("sudo reboot");
}

void GUIInterprocessVisitor::visit(communication::GUIShutdownResponse& data)
{
    auto command = ShutdownCommand();
    auto commandWrapper = SendingDataCommand(command.getFrameBytes());
    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);

    this_thread::sleep_for(std::chrono::milliseconds(100));

    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::REDUNDANT);

    this_thread::sleep_for(std::chrono::milliseconds(800));

    system("sudo shutdown now");
}
