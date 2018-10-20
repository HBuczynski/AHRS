#include "UIWelcomeState.h"
#include "UISetupState.h"

#include "../UIApplicationManager.h"

#include <thread>

using namespace std;
using namespace utility;
using namespace main_process;

UIWelcomeState::UIWelcomeState()
    :  UIAbstractState("UIWelcomeState", UIMainStateCode::WELCOME_PAGE)
{}

UIWelcomeState::~UIWelcomeState()
{}

void UIWelcomeState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{
    uiApplicationManager.setWelcomePage();

    if (logger_.isInformationEnable()) {
        const string message = string("UIWelcomeState :: Change to welcomePage.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    this_thread::sleep_for(4s);
    uiApplicationManager.communicationInProgress();
    setState(&uiApplicationManager, new UISetupState());
}

void UIWelcomeState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}

void UIWelcomeState::setInformationPage(UIApplicationManager &uiApplicationManager)
{

}
