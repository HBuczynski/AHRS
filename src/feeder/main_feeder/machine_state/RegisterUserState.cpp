#include "RegisterUserState.h"

using namespace utility;
using namespace std;

RegisterUserState::RegisterUserState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void RegisterUserState::runEntryEvent()
{}

void RegisterUserState::runExitEvent()
{}

void RegisterUserState::runInitEvent()
{

}
