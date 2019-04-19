#include "UISettingState.h"

UISettingState::UISettingState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UISettingState::runEntryEvent()
{

}

void UISettingState::runExitEvent()
{

}

void UISettingState ::runInitEvent()
{

}
