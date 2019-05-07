#ifndef AHRS_FLIGHTDATAMANAGER_H
#define AHRS_FLIGHTDATAMANAGER_H

#include <functional>
#include <vector>
#include <memory>
#include <logger/Logger.h>
#include <atomic>

#include <config_reader/FeederParameters.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>

namespace communication
{
    class FlightDataManager
    {
    public:
        FlightDataManager();
        ~FlightDataManager();

        void startFlightDataTransmission();
        void stopFlightDataTransmission();

        bool isActive();
        void registerFun(std::function<bool(std::vector<uint8_t> )> broadcastFun);

    private:
        void sendMeasurements();
        void initializeExternalSharedMemory();

        std::atomic<bool> runAcquisition_;
        std::thread acquisitionThread_;

        std::function<bool(std::vector<uint8_t> )> broadcastFunction_;

        config::FeederSharedMemory sharedMemoryParameters_;
        std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;

        utility::Logger& logger_;
    };
}

#endif
