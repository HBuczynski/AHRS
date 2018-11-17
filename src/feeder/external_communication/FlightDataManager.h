#ifndef AHRS_FLIGHTDATAMANAGER_H
#define AHRS_FLIGHTDATAMANAGER_H

#include <functional>
#include <vector>
#include <memory>
#include <logger/Logger.h>
#include <atomic>

namespace communication
{
    class FlightDataManager
    {
    public:
        FlightDataManager(std::function<bool(std::vector<uint8_t> )> broadcastFun);
        ~FlightDataManager();

        void startFlightDataTransmission();
        void stopFlightDataTransmission();

    private:
        void sendMeasurements();

        std::atomic<bool> runAcquisition_;
        std::thread acquisitionThread_;

        std::function<bool(std::vector<uint8_t> )> broadcastFunction_;
        utility::Logger& logger_;
    };
}

#endif