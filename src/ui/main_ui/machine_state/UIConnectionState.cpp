#include "UIConnectionState.h"

#include <interfaces/gui/GUIWindowCommand.h>

using namespace std;
using namespace utility;
using namespace communication;

UIConnectionState::UIConnectionState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UIConnectionState::runEntryEvent()
{}

void UIConnectionState::runExitEvent()
{}

void UIConnectionState::runInitEvent()
{
    auto command = GUIWindowCommand(PagesType::CONNECTING_PAGE);
    auto packet = command.getFrameBytes();
    guiCallback_(packet);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UIConnectionState :: Send ") + command.getName()
                 +  " " + to_string(static_cast<int>(command.getWindowType()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UIConnectionState::registerCallbackToGUI(function<void(vector<uint8_t>)> callback)
{
    guiCallback_ = callback;
}
