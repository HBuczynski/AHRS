#ifndef UIACQUISITIONSTATE_H
#define UIACQUISITIONSTATE_H

#include <hsm/State.h>

class UIAcquisitionState : public hsm::State
{
public:
    UIAcquisitionState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIACQUISITIONSTATE_H
