#include "CalibrationState.h"

using namespace utility;
using namespace std;

CalibrationState::CalibrationState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void CalibrationState::runEntryEvent()
{}

void CalibrationState::runExitEvent()
{}

void CalibrationState::runInitEvent()
{

}
