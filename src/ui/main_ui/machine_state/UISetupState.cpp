#include "UISetupState.h"
#include "../UIApplicationManager.h"

#include "UIAcquisitionState.h"

using namespace std;
using namespace utility;
using namespace main_process;

UISetupState::UISetupState()
    :  UIAbstractState("UISetupState", UIMainStateCode::ESTABLISHING_CONNECTION)
{

}

UISetupState::~UISetupState()
{

}

void UISetupState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UISetupState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UISetupState::setInformationPage(UIApplicationManager &uiApplicationManager)
{

}
