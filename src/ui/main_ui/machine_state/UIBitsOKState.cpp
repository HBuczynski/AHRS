#include "UIBitsOKState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

UIBitsOKState::UIBitsOKState()
        :  UIAbstractState("UIBitsOKState", UIMainStateCode::BITS_OK)
{}

UIBitsOKState::~UIBitsOKState()
{}

void UIBitsOKState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UIBitsOKState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UIBitsOKState::setInformationPage(UIApplicationManager &uiApplicationManager)
{

}
