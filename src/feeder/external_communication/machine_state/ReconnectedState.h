#ifndef AHRS_RECONNECTEDSTATE_H
#define AHRS_RECONNECTEDSTATE_H

#include <hsm/State.h>

namespace communication
{
    class ReconnectedState : public hsm::State
    {
    public:
        ReconnectedState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif
