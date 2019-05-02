#ifndef CALIBRATIONSTATE_H
#define CALIBRATIONSTATE_H

#include <functional>

#include <hsm/State.h>
#include <telemetry/IMUCalibrator.h>
#include <FeederDataContainer.h>
#include <interfaces/wireless_commands/CalibrateAccelerometerCommand.h>

class CalibrationState : public hsm::State
{
public:
    CalibrationState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void accelerometerAction(uint8_t axis, communication::AccelAction);
    void approveMagnetometer();

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void registerDataCallback(std::function<FeederDataContainer&()> getFeederData);
private:
    telemetry::IMUCalibrator imuCalibrator_;

    std::function<FeederDataContainer&()> getFeederData_;

};

#endif // CALIBRATIONSTATE_H
