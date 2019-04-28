#include "UIRedundantState.h"

UIRedundantState::UIRedundantState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent)
{}

void UIRedundantState::runEntryEvent()
{

}

void UIRedundantState::runExitEvent()
{

}

void UIRedundantState::runInitEvent()
{

}
