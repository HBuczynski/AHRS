#include "ExternalCommInterprocessVisitor.h"
#include "UIApplicationManager.h"

#include <interfaces/gui/GUIPlanesSetCommand.h>
#include <interfaces/gui/GUICallibrationCommand.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>

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
