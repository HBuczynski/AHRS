#ifndef UISETTINGSTATE_H
#define UISETTINGSTATE_H

#include <hsm/State.h>

class UISettingState : public hsm::State
{
public:
    UISettingState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UISETTINGSTATE_H
