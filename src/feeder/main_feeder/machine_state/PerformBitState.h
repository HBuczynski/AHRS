#ifndef PERFORMBITSTATE_H
#define PERFORMBITSTATE_H

#include <hsm/State.h>

class PerformBitState : public hsm::State
{
public:
    PerformBitState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // PERFORMBITSTATE_H
