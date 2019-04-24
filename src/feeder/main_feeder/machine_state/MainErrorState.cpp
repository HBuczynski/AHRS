#include "MainErrorState.h"

using namespace utility;
using namespace std;

MainErrorState::MainErrorState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void MainErrorState::runEntryEvent()
{}

void MainErrorState::runExitEvent()
{}

void MainErrorState::runInitEvent()
{

}
