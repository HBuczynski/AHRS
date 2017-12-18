#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include <waic_protocol/Command.h>

#include "CommandHandler.h"
#include "ClientThreadTCP.h"

#include <map>
#include <list>
#include <atomic>
#include <memory>
#include <utility>
#include <thread>

// Server located at the black box.
namespace communication
{
    class Server
    {
    public:
        Server(uint16_t port, uint8_t maxClientNumber);
        ~Server();

        void initializeHandlers(CallbackFunctions callbackFunctions);

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

        CallbackFunctions callbackFunctions_;
        std::list<std::unique_ptr<ClientThreadTCP> > clientList_;
    };
}
#endif