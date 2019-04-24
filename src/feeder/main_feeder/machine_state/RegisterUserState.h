#ifndef REGISTERUSERSTATE_H
#define REGISTERUSERSTATE_H

#include <hsm/State.h>

class RegisterUserState : public hsm::State
{
public:
    RegisterUserState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};


#endif // REGISTERUSERSTATE_H
