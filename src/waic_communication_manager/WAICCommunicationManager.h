#ifndef AHRS_BLACK_BOX_WAIC_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_WAIC_COMMUNICATION_MANAGER_H

#include <waic_server/WAICServer.h>
#include <waic_client/WAICClient.h>

#include <memory>
#include <list>
#include <utility>
#include <mutex>

namespace communication
{
    class WAICCommunicationManager
    {
    public:
        WAICCommunicationManager(uint16_t serverPort, uint8_t maxUserNumber);
        ~WAICCommunicationManager();

        void initialize();

        const std::list<std::pair<std::shared_ptr<WAICClient>, uint8_t > >& getClientList();
        void insertNewClient(std::pair<std::shared_ptr<WAICClient>, uint8_t > newClient);
        void removeClient(uint8_t id);

    private:
        void registerHandlers();
        void activateServer();

        std::shared_ptr<WAICServer> server_;
        std::mutex listMutex;
        std::list<std::pair<std::shared_ptr<WAICClient>, uint8_t >> clientList;
    };
}
#endif