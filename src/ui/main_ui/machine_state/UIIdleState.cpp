#include "UIIdleState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

UIIdleState::UIIdleState()
        :  UIAbstractState("UIIdleState", UIMainStateCode::IDLE)
{}

UIIdleState::~UIIdleState()
{}

void UIIdleState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UIIdleState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}