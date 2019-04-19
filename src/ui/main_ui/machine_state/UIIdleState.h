#ifndef UIIDLESTATE_H
#define UIIDLESTATE_H

#include <hsm/State.h>

class UIIdleState : public hsm::State
{
public:
    UIIdleState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIIDLESTATE_H
