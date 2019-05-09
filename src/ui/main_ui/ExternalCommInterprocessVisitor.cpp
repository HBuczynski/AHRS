#include "ExternalCommInterprocessVisitor.h"
#include "UIApplicationManager.h"

#include <interfaces/gui/GUIPlanesSetCommand.h>
#include <interfaces/gui/GUICallibrationCommand.h>
#include <interfaces/gui/GUIBITSCommand.h>
#include <interfaces/communication_process_ui/DatabaseHashCommand.h>
#include <interfaces/wireless_responses/BITsResponse.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_commands/SetHashCommand.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>

#include <interfaces/wireless_responses/ResponseFactory.h>

using namespace std;
using namespace utility;
using namespace main_process;
using namespace communication;

ExternalCommInterprocessVisitor::ExternalCommInterprocessVisitor(UIApplicationManager *uiApplicationManager)
    :   informationParameters_(42, 42, 42, 42),
        uiApplicationManager_(uiApplicationManager),
        logger_(Logger::getInstance())

{}

ExternalCommInterprocessVisitor::~ExternalCommInterprocessVisitor()
{}

void ExternalCommInterprocessVisitor::visit(ReceivingDataNotification& command)
{
    ResponseFactory responseFactory;

    auto response = responseFactory.createCommand(command.getData());

    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor:: Received - ") + response->getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    switch (response->getResponseType())
    {
        case ResponseType::CALIBRATING_STATUS :
        {
            const auto calibratingStatus = static_pointer_cast<CalibratingStatusResponse, Response>(responseFactory.createCommand(command.getData()));

            GUICallibrationCommand command(calibratingStatus->getCalibrationConfiguration(), calibratingStatus->getMode());
            uiApplicationManager_->sendToGUIProcess(command.getFrameBytes());
            break;
        }
        case ResponseType::PLANES_DATASET :
        {
            const auto planeDataSet = static_pointer_cast<PlanesDatasetResponse, Response>(responseFactory.createCommand(command.getData()));
            const auto planes = planeDataSet->getDataset();

            GUIPlanesSetCommand guiCommand(planes);
            uiApplicationManager_->sendToGUIProcess(guiCommand.getFrameBytes());
            break;
        }
        case ResponseType::BITs_STATUS :
        {
            const auto bits = static_pointer_cast<BITsResponse, Response>(responseFactory.createCommand(command.getData()));

            GUIBITSCommand bitsCommand(bits->getBits());
            uiApplicationManager_->sendToGUIProcess(bitsCommand.getFrameBytes());
            break;
        }
        default :
            break;
    }
}

void ExternalCommInterprocessVisitor::visit(CommunicationStatusNotification& command)
{
    const auto status = command.getState();

    switch(status)
    {
        case UIExternalComCode::INIT_CONNECTION :
        {
            uiApplicationManager_->handleEvent("SET_SETTINGS");
            auto hashCommand = SetHashCommand(uiApplicationManager_->getDbHash());
            auto commandWrapper = SendingDataCommand(hashCommand.getFrameBytes());
            uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);

            break;
        }
        case UIExternalComCode::RECONNECTED :
        case UIExternalComCode::REDUNDANT :
        case UIExternalComCode::MASTER :
        case UIExternalComCode::ERROR :
        case UIExternalComCode::IDLE :
        default:
            break;
    }
}

void ExternalCommInterprocessVisitor::visit(DatabaseNameNotification& command)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ExternalCommInterprocessVisitor:: Received - ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    DatabaseHashCommand hashCommand(uiApplicationManager_->getDbHash(), uiApplicationManager_->getDbName());
    uiApplicationManager_->sendToExternalCommunicationProcess(hashCommand.getFrameBytes(), command.getMode());
}
