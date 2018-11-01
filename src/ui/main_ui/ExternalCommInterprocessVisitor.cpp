#include "ExternalCommInterprocessVisitor.h"
#include "UIApplicationManager.h"

#include "ui/main_ui/machine_state/UIAcquisitionState.h"

#include <interfaces/wireless_commands/PerformBITsCommand.h>
#include <interfaces/wireless_responses/ResponseFactory.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>

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

    const auto response = responseFactory.createCommand(command.getData());

    if(logger_.isInformationEnable())
    {
        const string message = string("ExternalCommInterprocessVisitor:: Received - ") + response->getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    switch (response->getResponseType())
    {
        case ResponseType::BITs_STATUS :
        {
            get<2>(informationParameters_) = 1;

            uiApplicationManager_->setInformationPage(get<0>(informationParameters_), get<1>(informationParameters_),
                    get<2>(informationParameters_), get<3>(informationParameters_));
        }
    }
}

void ExternalCommInterprocessVisitor::visit(CommunicationStatusNotification& command)
{
    const auto status = command.getState();

    switch(status)
    {
        case UIExternalStateCode::MASTER :
        {
            get<0>(informationParameters_) = 1;
            uiApplicationManager_->setInformationPage(get<0>(informationParameters_), get<1>(informationParameters_),
                    get<2>(informationParameters_), get<3>(informationParameters_));

            auto performBIT = PerformBITsCommand();
            auto wrapCommand = SendingDataCommand(performBIT.getFrameBytes());

            uiApplicationManager_->sendToExternalCommunicationProcess(wrapCommand.getFrameBytes(),
                    config::UICommunicationMode::MASTER);

            break;
        }
        case UIExternalStateCode::IDLE :
        {
            break;
        }
        case UIExternalStateCode::REDUNDANT :
        {
            get<1>(informationParameters_) = 1;
            uiApplicationManager_->setInformationPage(get<0>(informationParameters_), get<1>(informationParameters_),
                    get<2>(informationParameters_), get<3>(informationParameters_));

            auto performBIT = PerformBITsCommand();
            auto wrapCommand = SendingDataCommand(performBIT.getFrameBytes());

            uiApplicationManager_->sendToExternalCommunicationProcess(wrapCommand.getFrameBytes(),
                    config::UICommunicationMode::MASTER);

            break;
        }
        case UIExternalStateCode::ERROR :
        {

            break;
        }
        default:

            break;
    }
}
