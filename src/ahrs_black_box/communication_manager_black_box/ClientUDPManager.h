#ifndef AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H
#define AHRS_BLACK_BOX_CALLBACKFUNCTIONS_H

#include <ahrs_black_box/client_udp/ClientUDP.h>

#include <list>
#include <cstdint>
#include <memory>
#include <mutex>
#include <utility>

namespace communication
{
    class ClientUDPManager
    {
    public:
        ClientUDPManager() {};
        virtual ~ClientUDPManager() {};

        virtual const std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t > >& getClientList() = 0;
        virtual void insertNewClient(std::pair<std::shared_ptr<ClientUDP>, uint8_t > newClient) = 0;
        virtual void removeClient(uint8_t id) = 0;

    protected:
        std::mutex clientListMutex_;
        std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t> > clientList_;
    };
}
#endif