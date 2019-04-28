#include "InitConnectionState.h"

using namespace utility;
using namespace std;

InitConnectionState::InitConnectionState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void InitConnectionState::runEntryEvent()
{}

void InitConnectionState::runExitEvent()
{}

void InitConnectionState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- ConnectionState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
