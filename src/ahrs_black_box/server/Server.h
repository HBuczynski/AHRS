#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include <protocol/Command.h>

#include "CommandHandlerVisitor.h"
#include "ClientThreadTCP.h"

#include <map>
#include <list>
#include <atomic>
#include <memory>
#include <utility>
#include <thread>

namespace communication
{
    class Server
    {
    public:
        Server(uint16_t port, uint8_t maxClientNumber, ClientUDPManager *clientUDPManager);
        ~Server();

        void startUserActivation();
        void stopUserActivation();
        void stopDataListening();

    private:
        void activateUsers();
        void updateClientList();

        uint16_t port_;
        uint8_t maxClientNumber_;

        std::atomic<bool> runUserActivation_;
        std::thread activationThread_;

        ClientUDPManager* clientUDPManager_;
        std::list<std::unique_ptr<ClientThreadTCP> > clientList_;
    };
}
#endif