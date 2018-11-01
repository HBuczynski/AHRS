#ifndef AHRS_FLIGHTDATAMANAGER_H
#define AHRS_FLIGHTDATAMANAGER_H

#include "ClientUDPManager.h"

#include <memory>
#include <logger/Logger.h>
#include <atomic>

namespace communication
{
    class FlightDataManager
    {
    public:
        FlightDataManager(std::shared_ptr<ClientUDPManager> clientUDPManager);
        ~FlightDataManager();

        void startFlightDataTransmission();
        void stopFlightDataTransmission();

    private:
        void sendMeasurements();

        std::atomic<bool> runAcquisition_;
        std::thread acquisitionThread_;

        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        utility::Logger& logger_;
    };
}

#endif