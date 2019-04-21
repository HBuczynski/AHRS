#include "UIIdleState.h"

using namespace std;
using namespace utility;

UIIdleState::UIIdleState(const string &name, shared_ptr<State> parent)
    : State(name, parent)
{}

void UIIdleState::runEntryEvent()
{}

void UIIdleState::runExitEvent()
{}

void UIIdleState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- UIIdleState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    registerInternalState_("LaunchState");
}
