#include "MainAcqState.h"

using namespace utility;
using namespace std;

MainAcqState::MainAcqState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void MainAcqState::runEntryEvent()
{}

void MainAcqState::runExitEvent()
{}

void MainAcqState::runInitEvent()
{

}
