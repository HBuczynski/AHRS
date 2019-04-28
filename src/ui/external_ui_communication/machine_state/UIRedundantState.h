#ifndef UIREDUNDANTSTATE_H
#define UIREDUNDANTSTATE_H

#include <hsm/State.h>

class UIRedundantState : public hsm::State
{
public:
    UIRedundantState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIREDUNDANTSTATE_H
