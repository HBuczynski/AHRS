#ifndef AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H
#define AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H

#include <interfaces/wireless_commands/CallibrateMagnetometerCommand.h>

#include "ClientUDP.h"
#include "FlightDataManager.h"

#include <list>
#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

namespace communication
{
    class ClientUDPManager
    {
    public:
        ClientUDPManager();
        ~ClientUDPManager();

        // Communication methods
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t > > getClientList();
        void insertNewClient(std::pair<std::shared_ptr<ClientUDP>, uint8_t > newClient);
        void removeClient(uint8_t id);

        bool broadcast(std::vector<uint8_t> frame);

    private:
        std::unique_ptr<FlightDataManager> flightDataManager_;

        std::mutex clientListMutex_;
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t> > clientList_;

        utility::Logger& logger_;
    };
}
#endif
