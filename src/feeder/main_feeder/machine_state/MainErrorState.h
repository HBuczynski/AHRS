#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include <hsm/State.h>

class MainErrorState : public hsm::State
{
public:
    MainErrorState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // ERRORSTATE_H
