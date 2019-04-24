#ifndef AHRS_IDLESTATE_H
#define AHRS_IDLESTATE_H

#include <hsm/State.h>

namespace communication
{
    class IdleState : public hsm::State
    {
    public:
        IdleState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif
