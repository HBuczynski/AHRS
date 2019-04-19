#ifndef UIIDLECOMMSTATE_H
#define UIIDLECOMMSTATE_H

#include <hsm/State.h>

class UIIdleCommState : public hsm::State
{
public:
    UIIdleCommState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIIDLECOMMSTATE_H
