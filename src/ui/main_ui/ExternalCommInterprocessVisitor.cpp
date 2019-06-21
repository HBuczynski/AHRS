#include "ExternalCommInterprocessVisitor.h"
#include "UIApplicationManager.h"

#include <interfaces/gui/GUIPlanesSetCommand.h>
#include <interfaces/gui/GUICallibrationCommand.h>
#include <interfaces/gui/GUIBITSCommand.h>
#include <interfaces/gui/GUIWindowCommand.h>
#include <interfaces/communication_process_ui/DatabaseHashCommand.h>
#include <interfaces/wireless_responses/BITsResponse.h>
#include <interfaces/wireless_responses/PlanesDatasetResponse.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_commands/SetHashCommand.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>
#include <interfaces/wireless_commands/HandshakeCommand.h>
#include <interfaces/wireless_commands/ChangeStateCommand.h>
#include <interfaces/wireless_responses/FeederStateCodeResponse.h>

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
        case ResponseType::FEEDER_STATE_CODE_RES :
        {
            const auto stateResponse = static_pointer_cast<FeederStateCodeResponse, Response>(responseFactory.createCommand(command.getData()));
            const auto feederState = stateResponse->getStateCode();

            handleFeederState(feederState);

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
            auto hashCommand = SetHashCommand(uiApplicationManager_->getDbHash());
            auto commandWrapper = SendingDataCommand(hashCommand.getFrameBytes());
            uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);

            this_thread::sleep_for(std::chrono::milliseconds(50));

            auto handshake = HandshakeCommand();
            auto handshakeWrapper = SendingDataCommand(handshake.getFrameBytes());
            uiApplicationManager_->sendToExternalCommunicationProcess(handshakeWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);
            break;
        }
        case UIExternalComCode::MASTER :
        case UIExternalComCode::RECONNECTED :
        case UIExternalComCode::REDUNDANT :
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

void ExternalCommInterprocessVisitor::handleFeederState(FeederStateCode feederCode)
{
    cout << "FeederCode: " << static_cast<int>(feederCode) << endl;
    cout << "State: " << uiApplicationManager_->getCurrentStateName() << endl;

    if(uiApplicationManager_->getCurrentStateName() == "AcquisitionState")
    {
        if (feederCode != FeederStateCode::MAIN_ACQ)
        {
            auto changeState = ChangeStateCommand(FeederStateCode::MAIN_ACQ);
            auto commandWrapper = SendingDataCommand(changeState.getFrameBytes());
            uiApplicationManager_->sendToExternalCommunicationProcess(commandWrapper.getFrameBytes(), config::UICommunicationMode::MASTER);
        }
    }
    else
    {
        if (feederCode == FeederStateCode::MAIN_ACQ || feederCode == FeederStateCode::STOP_ACQ)
        {
            uiApplicationManager_->handleEvent("BACK_2_ACQ");

            GUIWindowCommand guiWindow(PagesType::AHRS_PAGE);
            auto guiPacket = guiWindow.getFrameBytes();
            uiApplicationManager_->sendToGUIProcess(guiPacket);
        }
        else
            uiApplicationManager_->handleEvent("SET_SETTINGS");
    }
}
