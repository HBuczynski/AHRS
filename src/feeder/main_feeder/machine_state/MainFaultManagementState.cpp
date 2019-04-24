#include "MainFaultManagementState.h"

using namespace utility;
using namespace std;

MainFaultManagementState::MainFaultManagementState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void MainFaultManagementState::runEntryEvent()
{}

void MainFaultManagementState::runExitEvent()
{}

void MainFaultManagementState::runInitEvent()
{

}
