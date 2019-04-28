#ifndef CALIBRATIONSTATE_H
#define CALIBRATIONSTATE_H

#include <hsm/State.h>

class CalibrationState : public hsm::State
{
public:
    CalibrationState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;
};

#endif // CALIBRATIONSTATE_H
