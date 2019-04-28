#ifndef UIRECONNECTEDSTATE_H
#define UIRECONNECTEDSTATE_H

#include <hsm/State.h>

class UIReconnectedState : public hsm::State
{
public:
    UIReconnectedState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIRECONNECTEDSTATE_H
