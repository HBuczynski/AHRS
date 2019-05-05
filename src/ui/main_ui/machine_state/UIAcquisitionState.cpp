#include "UIAcquisitionState.h"

#include <interfaces/wireless_commands/StartAcquisitionCommand.h>
#include <interfaces/communication_process_ui/SendingDataCommand.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

UIAcquisitionState::UIAcquisitionState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UIAcquisitionState::runEntryEvent()
{}

void UIAcquisitionState::runExitEvent()
{}

void UIAcquisitionState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- UIAcquisitionState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    auto command = StartAcquisitionCommand();
    auto commandWrapper = SendingDataCommand(command.getFrameBytes());

    callback_(commandWrapper.getFrameBytes(), UICommunicationMode::MASTER);
}

void UIAcquisitionState::registerCallbackToExternalComm(function<void(vector<uint8_t>, UICommunicationMode)> callback)
{
    callback_ = callback;
}
