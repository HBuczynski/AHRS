#ifndef AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H
#define AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H

#include "AbstractState.h"
#include "ClientUDP.h"

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

        void broadcast(std::vector<uint8_t> frame);


        // Managing finite machine state

        void acceptedUsers();
        void startCalibration();
        void startDataSending();
        void restartProcess();
        void shutdownProcess();

        void setNewState(AbstractState *newState);

    private:
        std::unique_ptr<AbstractState> currentState_;

        std::mutex clientListMutex_;
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t> > clientList_;

        utility::Logger& logger_;
    };
}
#endif