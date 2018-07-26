#ifndef AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H
#define AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H

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

        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t > > getClientList();
        void insertNewClient(std::pair<std::shared_ptr<ClientUDP>, uint8_t > newClient);
        void removeClient(uint8_t id);

        void broadcast(std::vector<uint8_t> frame);

    private:
        std::mutex clientListMutex_;
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t> > clientList_;
    };
}
#endif