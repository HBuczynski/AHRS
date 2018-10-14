#include "UIEstablishingConnectionState.h"
#include "../UIApplicationManager.h"

#include "UICommunicationState.h"

using namespace std;
using namespace utility;
using namespace main_process;

UIEstablishingConnectionState::UIEstablishingConnectionState()
    :  UIAbstractState("UIEstablishingConnectionState", UIMainStateCode::ESTABLISHING_CONNECTION)
{

}

UIEstablishingConnectionState::~UIEstablishingConnectionState()
{

}

void UIEstablishingConnectionState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UIEstablishingConnectionState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UIEstablishingConnectionState::setInformationPage(UIApplicationManager &uiApplicationManager)
{
    uiApplicationManager.setInformationPage();

    if (logger_.isInformationEnable()) {
        const string message = string("UIWelcomeState :: Change to UIEstablishingConnectionState.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    setState(&uiApplicationManager, new UICommunicationState());
}
