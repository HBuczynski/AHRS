#include "UISettingState.h"
#include <interfaces/gui/GUIWindowCommand.h>

using namespace std;
using namespace utility;
using namespace communication;

UISettingState::UISettingState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UISettingState::runEntryEvent()
{

}

void UISettingState::runExitEvent()
{

}

void UISettingState::runInitEvent()
{
    auto command = GUIWindowCommand(PagesType::MENU_PAGE);
    auto packet = command.getFrameBytes();
    guiCallback_(packet);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UISettingState :: Send ") + command.getName()
                 +  " " + to_string(static_cast<int>(command.getWindowType()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UISettingState::registerCallbackToGUI(function<void(vector<uint8_t>)> callback)
{
    guiCallback_ = callback;
}
