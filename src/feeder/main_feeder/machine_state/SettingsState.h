#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <hsm/State.h>

class SettingsState : public hsm::State
{
public:
    SettingsState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // SETTINGSSTATE_H
