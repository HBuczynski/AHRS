#include "UIWelcameState.h"
#include "UIEstablishingConnectionState.h"

#include "../UIApplicationManager.h"

#include <thread>

using namespace std;
using namespace utility;
using namespace main_process;

UIWelcameState::UIWelcameState()
    :  UIAbstractState("UIWelcameState", UIMainStateCode::WELCOME_PAGE)
{
}

UIWelcameState::~UIWelcameState()
{}

void UIWelcameState::setWelcomePage(UIApplicationManager &uiApplicationManager)
{
    uiApplicationManager.setWelcomePage();

    if (logger_.isInformationEnable()) {
        const string message = string("UIWelcameState :: Change to welcomePage.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    this_thread::sleep_for(2s);
    uiApplicationManager.communicationInProgress();
    setState(&uiApplicationManager, new UIEstablishingConnectionState());
}

void UIWelcameState::communicationInProgress(UIApplicationManager &uiApplicationManager)
{

}
