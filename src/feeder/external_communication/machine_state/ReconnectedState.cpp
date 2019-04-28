#include "ReconnectedState.h"

using namespace std;
using namespace utility;
using namespace communication;

ReconnectedState::ReconnectedState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void ReconnectedState::runEntryEvent()
{}

void ReconnectedState::runExitEvent()
{}

void ReconnectedState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-EXTCOM- ReconnectedState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
