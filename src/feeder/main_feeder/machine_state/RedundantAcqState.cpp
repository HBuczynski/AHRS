#include "RedundantAcqState.h"

using namespace utility;
using namespace std;

RedundantAcqState::RedundantAcqState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void RedundantAcqState::runEntryEvent()
{}

void RedundantAcqState::runExitEvent()
{}

void RedundantAcqState::runInitEvent()
{

}
