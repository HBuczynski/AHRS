#ifndef MAINFAULTMAANAGEMENTSTATE_H
#define MAINFAULTMAANAGEMENTSTATE_H

#include <hsm/State.h>

class MainFaultManagementState : public hsm::State
{
public:
    MainFaultManagementState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // MAINFAULTMAANAGEMENTSTATE_H
