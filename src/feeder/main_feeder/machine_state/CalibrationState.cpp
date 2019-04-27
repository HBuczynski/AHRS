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
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- CalibrationState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
