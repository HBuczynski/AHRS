#ifndef UISETTINGSTATE_H
#define UISETTINGSTATE_H

#include <vector>
#include <functional>
#include <hsm/State.h>

class UISettingState : public hsm::State
{
public:
    UISettingState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void registerCallbackToGUI(std::function<void(std::vector<uint8_t>)> callback);

private:
    std::function<void(std::vector<uint8_t>)> guiCallback_;
};

#endif // UISETTINGSTATE_H
