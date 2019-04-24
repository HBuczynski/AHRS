#include "ReconnectedState.h"

using namespace communication;

ReconnectedState::ReconnectedState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void ReconnectedState::runEntryEvent()
{}

void ReconnectedState::runExitEvent()
{}

void ReconnectedState::runInitEvent()
{}
