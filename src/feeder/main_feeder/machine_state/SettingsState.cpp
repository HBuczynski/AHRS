#include "SettingsState.h"

using namespace utility;
using namespace std;

SettingsState::SettingsState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void SettingsState::runEntryEvent()
{}

void SettingsState::runExitEvent()
{}

void SettingsState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- SettingsState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
