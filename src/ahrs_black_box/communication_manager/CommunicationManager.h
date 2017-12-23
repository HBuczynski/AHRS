#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <server/Server.h>
#include <client/Client.h>

#include <memory>
#include <list>
#include <utility>
#include <mutex>

namespace communication
{
    class CommunicationManager : public ClientUDPManager
    {
    public:
        CommunicationManager(uint16_t serverPort, uint8_t maxUserNumber);
        ~CommunicationManager();

        void initialize();

        const std::list<std::pair<std::shared_ptr<Client>, uint8_t > >& getClientList() override;
        void insertNewClient(std::pair<std::shared_ptr<Client>, uint8_t > newClient) override;
        void removeClient(uint8_t id) override;

    private:
        void activateServer();

        std::shared_ptr<Server> server_;
    };
}
#endif