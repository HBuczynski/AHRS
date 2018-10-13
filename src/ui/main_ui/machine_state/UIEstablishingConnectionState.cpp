#include "UIEstablishingConnectionState.h"
#include "../UIApplicationManager.h"

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
