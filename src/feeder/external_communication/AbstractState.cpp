#include "AbstractState.h"

#include "ClientUDPManager.h"

using namespace std;
using namespace machine_state;
using namespace communication;

AbstractState::AbstractState(string name)
    :   name_(name)
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
