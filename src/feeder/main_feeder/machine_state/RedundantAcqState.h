#ifndef REDUNDANTACQSTATE_H
#define REDUNDANTACQSTATE_H

#include <hsm/State.h>

class RedundantAcqState : public hsm::State
{
public:
    RedundantAcqState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // REDUNDANTACQSTATE_H
