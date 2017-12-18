#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <waic_server/Server.h>
#include <waic_client/Client.h>

#include <memory>
#include <list>
#include <utility>
#include <mutex>

namespace communication
{
    class CommunicationManager
    {
    public:
        CommunicationManager(uint16_t serverPort, uint8_t maxUserNumber);
        ~CommunicationManager();

        void initialize();

        const std::list<std::pair<std::shared_ptr<Client>, uint8_t > >& getClientList();
        void insertNewClient(std::pair<std::shared_ptr<Client>, uint8_t > newClient);
        void removeClient(uint8_t id);

    private:
        void activateServer();

        std::shared_ptr<Server> server_;
        std::mutex clientListMutex_;

        std::list<std::pair<std::shared_ptr<Client>, uint8_t> > clientList_;
        CallbackFunctions callbackFunctions_;
    };
}
#endif