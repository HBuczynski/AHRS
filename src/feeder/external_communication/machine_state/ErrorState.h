#ifndef AHRS_ERRORSTATE_H
#define AHRS_ERRORSTATE_H

#include <hsm/State.h>

namespace communication
{
    class ErrorState : public hsm::State
    {
    public:
        ErrorState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif
