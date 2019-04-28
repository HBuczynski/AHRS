#ifndef MAINACQSTATE_H
#define MAINACQSTATE_H

#include <hsm/State.h>

class MainAcqState : public hsm::State
{
public:
    MainAcqState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // MAINACQSTATE_H
