#ifndef AHRS_INITCONNECTIONSTATE_H
#define AHRS_INITCONNECTIONSTATE_H

#include <hsm/State.h>

namespace communication
{
    class InitConnectionState : public hsm::State
    {
    public:
        InitConnectionState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}
#endif
