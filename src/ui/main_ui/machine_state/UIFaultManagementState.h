#ifndef UIFaultManagementState_H
#define UIFaultManagementState_H

#include <hsm/State.h>

class UIFaultManagementState : public hsm::State
{
public:
    UIFaultManagementState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIFaultManagementState_H
