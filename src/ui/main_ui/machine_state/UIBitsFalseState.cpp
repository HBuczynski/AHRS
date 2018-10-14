#include "UIBitsFalseState.h"

#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

UIBitsFalseState::UIBitsFalseState()
        :  UIAbstractState("UIBitsFalseState", UIMainStateCode::BITS_FALSE)
{}

UIBitsFalseState::~UIBitsFalseState()
{}

void UIBitsFalseState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{

}

void UIBitsFalseState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UIBitsFalseState::setInformationPage(UIApplicationManager &uiApplicationManager)
{

}
