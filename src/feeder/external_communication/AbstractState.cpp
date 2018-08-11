#include "AbstractState.h"

#include "ClientUDPManager.h"

using namespace std;
using namespace utility;
using namespace communication;

AbstractState::AbstractState(string name)
    :   name_(name),
        logger_(Logger::getInstance())
{ }

AbstractState::~AbstractState()
{ }

const string& AbstractState::getName() const
{
    return name_;

}

void AbstractState::setState(ClientUDPManager *machine, AbstractState *state)
{
    machine->setNewState(state);
}
