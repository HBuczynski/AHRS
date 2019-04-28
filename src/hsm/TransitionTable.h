#ifndef ALEXASIMULATOR_TRANSITIONTABLE_H
#define ALEXASIMULATOR_TRANSITIONTABLE_H

#include "State.h"
#include <vector>

namespace hsm
{
    using TranasitionElement = std::tuple<std::shared_ptr<State>, Event, std::shared_ptr<State>>;

    class TransitionTable final
    {
    public:
        TransitionTable() = delete;
        TransitionTable(std::initializer_list<TranasitionElement> transitionTable);

        void addUnboundState(std::shared_ptr<State> state);
        void initializeHSMCallbacks(Callback handleEvent, Callback registerInternalState);

        Event getEvent(std::string key);
        std::shared_ptr<State> getState(std::string id);
        const std::vector<TranasitionElement> &getTransitionTable() const noexcept;

        std::string showTable() const noexcept;
    private:
        void addNewEvent(Event event);

        std::unordered_map<std::string, std::shared_ptr<State> > states_;
        std::unordered_map<std::string, Event> events_;
        std::vector<TranasitionElement> transitionVector_;
    };
}

#endif //ALEXASIMULATOR_TRANSITIONTABLE_H
