#ifndef UIMASTERSTATE_H
#define UIMASTERSTATE_H

#include <hsm/State.h>

class UIMasterState : public hsm::State
{
public:
    UIMasterState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // UIMASTERSTATE_H
