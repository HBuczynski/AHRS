#include "GUIInterprocessVisitor.h"

#include <config_reader/UIParameters.h>
#include <interfaces/wireless_commands/StartAcquisitionCommand.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>

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
{}

void GUIInterprocessVisitor::visit(communication::GUIWindowResponse &data)
{
    auto command = StartAcquisitionCommand();
    auto commandWrapper = SendingDataCommand(command.getFrameBytes());

    uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN-GUIInterprocessVisitor:: Received - ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
