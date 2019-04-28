#ifndef UIINITCONNECTIONSTATE_H
#define UIINITCONNECTIONSTATE_H

#include <hsm/State.h>

class UIInitConnectionState : public hsm::State
{
public:
    UIInitConnectionState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIINITCONNECTIONSTATE_H
