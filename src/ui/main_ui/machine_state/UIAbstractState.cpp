#include "UIAbstractState.h"
#include "../UIApplicationManager.h"

using namespace std;
using namespace utility;
using namespace main_process;

UIAbstractState::UIAbstractState(std::string name, UIMainStateCode stateCode)
    : stateCode_(stateCode),
      name_(name),
      logger_(Logger::getInstance())
{}

UIAbstractState::~UIAbstractState()
{}

const UIMainStateCode &UIAbstractState::getStateCode() const
{
    return stateCode_;
}

const string &UIAbstractState::getName() const
{
    return name_;
}

void UIAbstractState::setState(UIApplicationManager *machine, UIAbstractState *state)
{
    machine->setNewState(state);
}
