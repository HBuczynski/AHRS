#include "UICallibrationState.h"

#include <interfaces/wireless_commands/CalibrateDataCommand.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

UICallibrationState::UICallibrationState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UICallibrationState::runEntryEvent()
{}

void UICallibrationState::runExitEvent()
{}

void UICallibrationState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- UICallibrationState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

 void UICallibrationState::registerCallbackToExternalComm(function<void(vector<uint8_t>, UICommunicationMode)> callback)
 {
     callback_ = callback;
 }
