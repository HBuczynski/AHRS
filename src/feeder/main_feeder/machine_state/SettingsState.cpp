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

}
