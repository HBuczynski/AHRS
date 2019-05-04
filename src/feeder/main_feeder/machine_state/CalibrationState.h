#ifndef CALIBRATIONSTATE_H
#define CALIBRATIONSTATE_H

#include <atomic>
#include <functional>

#include <hsm/State.h>
#include <telemetry/CalibrationManager.h>
#include <FeederDataContainer.h>


class CalibrationState : public hsm::State
{
public:
    CalibrationState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void accelerometerAction(uint8_t axis, communication::AccelAction action);
    void approveMagnetometer();

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void registerDataCallback(std::function<FeederDataContainer&()> getFeederData);
private:
    telemetry::CalibrationManager calibrationManager_;

    std::function<FeederDataContainer&()> getFeederData_;

};

#endif // CALIBRATIONSTATE_H
