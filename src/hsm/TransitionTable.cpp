#include <sstream>
#include <cassert>

#include "TransitionTable.h"

using namespace std;
using namespace hsm;

TransitionTable::TransitionTable(initializer_list<TranasitionElement> transitionTable)
{
    for(auto &element : transitionTable)
    {
        // Register transition in internal state's hash map.
        get<0>(element)->addTransition(get<1>(element), get<2>(element));

        // Add states to internal transition table's container using public method.
        addUnboundState(get<0>(element));
        addUnboundState(get<2>(element));
        // Register new event in the container.
        addNewEvent(get<1>(element));

        transitionVector_.push_back(element);
    }
}

void TransitionTable::initializeHSMCallbacks(Callback handleEvent, Callback registerInternalState)
{
    for(auto &state : states_)
    {
        state.second->initializeHSMCallbacks(handleEvent, registerInternalState);
    }
}

void TransitionTable::addNewEvent(Event event)
{
    const auto eventIter = events_.find(event.getKey());

    if(eventIter == events_.cend())
    {
        events_.insert({event.getKey(), event});
    }
}

void TransitionTable::addUnboundState(shared_ptr<State> state)
{
    const auto stateIter = states_.find(state->getName());

    if(stateIter == states_.cend())
    {
        states_[state->getName()] = state;
    }
}

Event TransitionTable::getEvent(string id)
{
    const auto eventIter = events_.find(id);

    if(eventIter != events_.cend())
    {
        return (*eventIter).second;
    }

    return Event{""};
}

shared_ptr<State> TransitionTable::getState(string id)
{
    const auto stateIter = states_.find(id);

    if(stateIter != states_.cend())
    {
        return states_[id];
    }

    return nullptr;
}

const vector<TranasitionElement> &TransitionTable::getTransitionTable() const noexcept
{
    return transitionVector_;
}

string TransitionTable::showTable() const noexcept
{
    stringstream log;
    uint16_t counter{0};

    log << "## Transition Table ##\n";
    for(const auto& transition : transitionVector_)
    {
        log << to_string(counter++) << ".\t" << get<0>(transition)->getName() << "\t\t-->\t"
                                             << get<1>(transition) << "\t\t-->\t"
                                             << get<2>(transition)->getName() << "\n";
    }

    return log.str();
}