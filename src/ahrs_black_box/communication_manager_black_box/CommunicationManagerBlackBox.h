#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <server_tcp/ServerTCP.h>
#include <client_udp/ClientUDP.h>

#include <memory>
#include <list>
#include <utility>
#include <mutex>

namespace communication
{
    class CommunicationManagerBlackBox : public ClientUDPManager
    {
    public:
        CommunicationManagerBlackBox(uint16_t serverPort, uint8_t maxUserNumber);
        ~CommunicationManagerBlackBox();

        void initialize();

        const std::list<std::pair<std::shared_ptr<ClientUDP>, uint8_t > >& getClientList() override;
        void insertNewClient(std::pair<std::shared_ptr<ClientUDP>, uint8_t > newClient) override;
        void removeClient(uint8_t id) override;

    private:
        void activateServer();

        std::shared_ptr<ServerTCP> server_;
    };
}
#endif