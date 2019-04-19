#ifndef UICALLIBRATIONSTATE_H
#define UICALLIBRATIONSTATE_H

#include <hsm/State.h>

class UICallibrationState : public hsm::State
{
public:
    UICallibrationState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UICALLIBRATIONSTATE_H
