#ifndef UILAUNCHSTATE_H
#define UILAUNCHSTATE_H

#include <vector>
#include <functional>
#include <hsm/State.h>

class UILaunchState : public hsm::State
{
public:
    UILaunchState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
    void registerCallbackToGUI(std::function<void(std::vector<uint8_t>)> callback);

private:
    std::function<void(std::vector<uint8_t>)> guiCallback_;
};

#endif // UILAUNCHSTATE_H
