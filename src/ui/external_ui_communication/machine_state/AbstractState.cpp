#include "AbstractState.h"
#include "CommunicationManagerUI.h"

using namespace std;
using namespace utility;
using namespace communication;

AbstractState::AbstractState::AbstractState(std::string name, UIExternalStateCode stateCode)
    :   stateCode_(stateCode),
        name_(name),
        logger_(Logger::getInstance())
{ }

AbstractState::AbstractState::~AbstractState()
{ }

const UIExternalStateCode &AbstractState::AbstractState::getStateCode() const
{
    return stateCode_;
}

const string &AbstractState::AbstractState::getName() const
{
    return name_;
}

void AbstractState::AbstractState::setState(CommunicationManagerUI *machine, AbstractState *state)
{
    machine->setNewState(state);
}
