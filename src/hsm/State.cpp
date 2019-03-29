#include "State.h"

#include <cassert>

using namespace std;
using namespace hsm;
using namespace utility;

State::State(const string &name, shared_ptr<State> parent)
    : handleEvent_(nullptr),
      registerInternalState_(nullptr),
      logger_(Logger::getInstance()),
      name_(move(name)),
      isCallbackInitialized(false),
      parent_(parent)
{}

void State::initializeHSMCallbacks(Callback handleEvent, Callback registerInternalState)
{
    if ( isCallbackInitialized )
        return;
    
    handleEvent_ = handleEvent;
    registerInternalState_ = registerInternalState;
}

void State::addTransition(Event event, shared_ptr<State> state)
{
    const auto stateIter = stateTable_.find(event);

    // Register new state in a hash map.
    if(stateIter == stateTable_.cend())
    {
        stateTable_[event] = state;
        return;
    }
    
    // User tried to add the same transition.
    if( (stateTable_[event].lock() != nullptr) && (stateTable_[event].lock()->getName() == state->getName()) )
    {
        if (logger_.isWarningEnable())
        {
            const string message = "State:: " + name_ + " - tried to add the same transition second time.";
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
        return;
    }
    
    // Transition is repeated.
    // Logical error - stops program work.
    if (logger_.isErrorEnable())
    {
        const string message = "State:: " + name_ + " - cannot assign event to - " + state->getName();
        logger_.writeLog(LogType::ERROR_LOG, message);
    }

    assert(0 && "You have tried to add another state to existing event.");
}

shared_ptr<State> State::moveToState(Event event)
{
    const auto stateIter = stateTable_.find(event);

    if(stateIter != stateTable_.cend())
    {
        auto nextState = stateTable_[event];
        return nextState.lock();
    }

    return nullptr;
}

const string &State::getName() const noexcept
{
    return name_;
}

shared_ptr<State> State::getParent() const noexcept
{
    return parent_.lock();
}

bool State::operator==(const State &rhs)
{
    return name_ == rhs.name_;
}

State &State::operator=(const State &rhs)
{
    parent_ = rhs.parent_;
    stateTable_ = rhs.stateTable_;

    name_ = rhs.name_;

    return *this;
}
