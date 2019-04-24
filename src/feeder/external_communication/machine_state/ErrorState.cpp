#include "ErrorState.h"

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

}


