#include "UILaunchState.h"

#include <interfaces/gui/GUIWindowCommand.h>

#include <thread>
#include <chrono>

using namespace std;
using namespace utility;
using namespace communication;

UILaunchState::UILaunchState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UILaunchState::runEntryEvent()
{}

void UILaunchState::runExitEvent()
{}

void UILaunchState::runInitEvent()
{
    auto command = GUIWindowCommand(PagesType::WELCOME_PAGE);
    auto packet = command.getFrameBytes();
    guiCallback_(packet);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- UILaunchState :: Send info master -> gui:") + command.getName()
                +  " " + to_string(static_cast<int>(command.getWindowType()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    this_thread::sleep_for(4s);
    handleEvent_("CONNECT");
}

void UILaunchState::registerCallbackToGUI(function<void(vector<uint8_t>)> callback)
{
    guiCallback_ = callback;
}
