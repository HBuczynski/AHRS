#ifndef MAINACQSTATE_H
#define MAINACQSTATE_H

#include <hsm/State.h>

#include <thread>
#include <atomic>

#include <database_manager/FeederDb.h>
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
    bool initializeDb(const std::string& name);
    void registerDataCallback(std::function<FeederDataContainer&()> getFeederData);

private:
    bool initializeExternalSharedMemory();
    bool initializeInternalSharedMemory();
    void runAcquisition();

    void calculateFlightParameters(FeederGeneralData& generalData);
    double calculateMachNo(double velocity, double altitude);
    void save2Database();

    std::shared_ptr<database::FeederDb> feederDb_;

    uint64_t previousTime_;
    double previousAltitude_;

    std::function<FeederDataContainer&()> getFeederData_;
    telemetry::PlaneOrientationHandler planeOrientation_;
    gps::GPSAdafruitInterface gpsAdafruit_;

    std::thread acqThread_;
    std::atomic<bool> runAcq_;

    std::thread dbThread_;
    std::atomic<bool> runDB_;

    static bool initialization_;

    config::FeederSharedMemory sharedMemoryParameters_;
    std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;
    std::unique_ptr<communication::SharedMemoryWrapper> internalSharedMemory_;
};

#endif // MAINACQSTATE_H
