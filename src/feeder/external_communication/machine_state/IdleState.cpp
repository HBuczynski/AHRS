#include "IdleState.h"

using namespace utility;
using namespace std;
using namespace communication;

IdleState::IdleState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void IdleState::runEntryEvent()
{}

void IdleState::runExitEvent()
{}

void IdleState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- UIIdleState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    registerInternalState_("ConnectionState");
}
