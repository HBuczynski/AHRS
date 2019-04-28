#ifndef UIERRORSTATE_H
#define UIERRORSTATE_H

#include <hsm/State.h>

class UIErrorState : public hsm::State
{
public:
    UIErrorState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIERRORSTATE_H
