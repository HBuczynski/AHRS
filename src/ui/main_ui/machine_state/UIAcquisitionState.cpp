#include "UIAcquisitionState.h"

#include "../UIApplicationManager.h"

using namespace main_process;

UIAcquisitionState::UIAcquisitionState()
        :  UIAbstractState("UIAcquisitionState", UIMainStateCode::COMMUNICATION_OK)
{}

UIAcquisitionState::~UIAcquisitionState()
{}

void UIAcquisitionState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UIAcquisitionState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UIAcquisitionState::setInformationPage(UIApplicationManager &uiApplicationManager)
{

}
