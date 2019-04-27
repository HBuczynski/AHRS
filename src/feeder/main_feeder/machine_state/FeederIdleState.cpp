#include "FeederIdleState.h"

using namespace utility;
using namespace std;

FeederIdleState::FeederIdleState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void FeederIdleState::runEntryEvent()
{}

void FeederIdleState::runExitEvent()
{}

void FeederIdleState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- IdleState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    registerInternalState_("ConnectionState");
}

