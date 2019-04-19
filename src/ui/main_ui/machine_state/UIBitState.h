#ifndef UIBITSTATE_H
#define UIBITSTATE_H

#include <hsm/State.h>

class UIBitState : public hsm::State
{
public:
    UIBitState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIBITSTATE_H
