#ifndef ALEXASIMULATOR_HSMINTERFACE_H
#define ALEXASIMULATOR_HSMINTERFACE_H

#include "TransitionTable.h"

namespace hsm
{
    class HSM
    {
    public:
        HSM(const std::string& name, const TransitionTable &transitionTable, std::shared_ptr<State> rootState);
        virtual ~HSM() = default;

        void startHSM();
        void handleEvent(const std::string &eventName) noexcept;

        const std::string& getCurrentStateName() const noexcept;
        std::shared_ptr<State> getState(const std::string& id) noexcept;

    private:
        void registerInternalState(const std::string &name) noexcept;
        void makeTransition(std::shared_ptr<State> state) noexcept;

        void tracePathToTargetState();

        uint16_t findCommonAncestor(std::shared_ptr<State> state);
        void exitToCommonAncestor(uint16_t toLCA);

        TransitionTable transitionTable_;
        const std::string NAME;

        std::shared_ptr<State> nextState_;
        std::shared_ptr<State> sourceState_;
        std::shared_ptr<State> currentState_;
        std::shared_ptr<State> rootState_;
    };
}

#endif
