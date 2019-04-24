#ifndef FEEDERIDLESTATE_H
#define FEEDERIDLESTATE_H

#include <hsm/State.h>

class FeederIdleState : public hsm::State
{
public:
    FeederIdleState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // FEEDERIDLESTATE_H
