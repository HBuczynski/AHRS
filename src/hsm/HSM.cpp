#include "HSM.h"
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace hsm;

HSM::HSM(const string& name, const TransitionTable &transitionTable, shared_ptr<State> rootState)
:     NAME(name),
      transitionTable_(transitionTable),
      nextState_(nullptr),
      sourceState_(nullptr),
      currentState_(nullptr),
      rootState_(rootState)
{
    assert((rootState != nullptr) && "You dont' initialized root state.");

    // Initialize static callbacks to allow states to register internal states
    // or handler event in specific situations.
    Callback handleEvent = bind(&HSM::handleEvent, this, std::placeholders::_1);
    Callback registerInternalState = bind(&HSM::registerInternalState, this, std::placeholders::_1);

    transitionTable_.initializeHSMCallbacks(handleEvent, registerInternalState);
    rootState_->initializeHSMCallbacks(handleEvent, registerInternalState);
}

void HSM::start()
{
    // Initialize current state as root.
    currentState_ = rootState_;
    currentState_->runEntryEvent();

    // Go from root to the leaf - starting point of the HSM.
    while (currentState_->runInitEvent(), nextState_.get())
    {
        tracePathToTargetState();
    }
}

void HSM::handleEvent(const std::string &eventName) noexcept
{
    const auto event = transitionTable_.getEvent(eventName);
    for(auto pathNode = currentState_; pathNode != nullptr; pathNode = pathNode->getParent())
    {
        // Register sourceState as a state which contains event.
        sourceState_= pathNode;
        // Check if state contains transition to event.
        auto state = sourceState_->moveToState(event);

        if ( state == nullptr )
            continue;

        // Find the common ancestor for source state and target state (in this case already next state).
        // Exit from source state to the common ancestor.
        makeTransition(state);

        if( nextState_ )
        {
            // Trace path from common ancestor to target state.
            tracePathToTargetState();

            while (currentState_->runInitEvent(), nextState_)
            {
                tracePathToTargetState();
            }
        }
    }
}

void HSM::tracePathToTargetState()
{
    vector<shared_ptr<State>> path;

    if(nextState_->getParent())
    {
        for (auto pathElement = nextState_; pathElement != currentState_; pathElement = pathElement->getParent())
        {
            path.push_back(pathElement);
        }

        for (auto iter = path.rbegin(); iter != path.rend(); ++iter)
        {
            (*iter)->runEntryEvent();
        }
    }

    currentState_ = nextState_;
    nextState_ = nullptr;
}

void HSM::registerInternalState(const string &name) noexcept
{
    nextState_ = transitionTable_.getState(name);
}

void HSM::makeTransition(shared_ptr<State> state) noexcept
{
    // Find common ancestor for source state of event and target state.
    const auto lca = findCommonAncestor(state);
    // Exit to ancestor state for both source and target state.
    exitToCommonAncestor(lca);

    nextState_ = state;
}

uint16_t HSM::findCommonAncestor(std::shared_ptr<State> targetState)
{
    if(sourceState_ != targetState)
    {
        uint16_t lsa = 0u;
        for(auto sourceParentState = sourceState_; sourceParentState != nullptr; ++lsa, sourceParentState = sourceParentState->getParent())
        {
            for (auto parentTargetState = targetState; parentTargetState != nullptr; parentTargetState = parentTargetState->getParent())
            {
                if(sourceParentState == parentTargetState)
                {
                    return lsa;
                }
            }
        }
        return 0;
    }

    return 1;
}

void HSM::exitToCommonAncestor(uint16_t toLCA)
{
    auto state = currentState_;

    while(state != sourceState_)
    {
        state->runExitEvent();
        state = state->getParent();
    }

    while(toLCA--)
    {
        state->runExitEvent();
        state = state->getParent();
    }

    currentState_ = state;
}
