#ifndef MAINACQSTATE_H
#define MAINACQSTATE_H

#include <hsm/State.h>

#include <thread>
#include <atomic>

#include <FeederDataContainer.h>
#include <hal/include/PlaneOrientationHandler.h>
#include <hal/include/GPSAdafruitInterface.h>

#include <config_reader/FeederParameters.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>

class MainAcqState : public hsm::State
{
public:
    MainAcqState(const std::string &name, std::shared_ptr<State> parent = nullptr);

    void runEntryEvent() override;
    void runExitEvent() override;
    void runInitEvent() override;

    void stopAcq();
    void registerDataCallback(std::function<FeederDataContainer&()> getFeederData);

private:
    bool initializeExternalSharedMemory();
    void runAcquisition();

    void calculateFlightParameters(FeederGeneralData& generalData);
    void writeGeneralData(FeederGeneralData& generalData);
    void save2Database(FeederGeneralData& generalData);

    std::function<FeederDataContainer&()> getFeederData_;
    telemetry::PlaneOrientationHandler planeOrientation_;
    gps::GPSAdafruitInterface gpsAdafruit_;

    std::thread acqThread_;
    std::atomic<bool> runAcq_;
    static bool initialization_;

    config::FeederSharedMemory sharedMemoryParameters_;
    std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;
};

#endif // MAINACQSTATE_H
