#include "ErrorState.h"

using namespace std;
using namespace utility;
using namespace communication;

ErrorState::ErrorState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void ErrorState::runEntryEvent()
{

}

void ErrorState::runExitEvent()
{

}

void ErrorState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-EXTCOM- ErrorState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}


