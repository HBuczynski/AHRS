#include "UIErrorState.h"

UIErrorState::UIErrorState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UIErrorState::runEntryEvent()
{

}

void UIErrorState::runExitEvent()
{

}

void UIErrorState::runInitEvent()
{

}
