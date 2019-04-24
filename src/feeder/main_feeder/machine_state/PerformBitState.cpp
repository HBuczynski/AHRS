#include "PerformBitState.h"

using namespace utility;
using namespace std;

PerformBitState::PerformBitState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void PerformBitState::runEntryEvent()
{}

void PerformBitState::runExitEvent()
{}

void PerformBitState::runInitEvent()
{

}
