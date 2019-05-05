#include "UIBitState.h"

#include <interfaces/wireless_commands/PerformBITsCommand.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

UIBitState::UIBitState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UIBitState::runEntryEvent()
{}

void UIBitState::runExitEvent()
{}

void UIBitState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- UIBitState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    PerformBITsCommand command;
    auto commandWrapper = SendingDataCommand(command.getFrameBytes());
    callback_(commandWrapper.getFrameBytes(), UICommunicationMode::MASTER);
}

 void UIBitState::registerCallbackToExternalComm(function<void(vector<uint8_t>, UICommunicationMode)> callback)
 {
     callback_ = callback;
 }
