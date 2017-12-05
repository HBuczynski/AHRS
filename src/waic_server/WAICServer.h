#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include <waic_protocol/WAICCommand.h>
#include <waic_packet/WAICStreamTCP.h>

#include "WAICCommandHandler.h"

#include <map>
#include <list>
#include <atomic>
#include <memory>
#include <utility>
#include <thread>

// Server located at the black box.
namespace communication
{
    struct ClientThread
    {
        std::thread clientThread;
        std::shared_ptr<WAICStreamTCP> streamTCP;
        uint8_t id;
    };

    class WAICServer
    {
    public:
        WAICServer(uint16_t portIn, uint8_t maxClientNumberIn);
        ~WAICServer();

        void startUserActivation();
        void stopUserActivation();

        void registerCommand(WAICCommandType type, std::shared_ptr<WAICCommandHandler> handler);
        void unregisterCommand(WAICCommandType type);

    private:
        void activateUsers();
        void listenData(std::shared_ptr<ClientThread> client);
        void removeClient(std::shared_ptr<ClientThread> client);

        uint16_t port;
        uint8_t maxClientNumber;
        std::atomic<uint8_t> clientsNumber;

        std::atomic<bool> runUserActivation;
        std::thread activationThread;

        std::list<std::shared_ptr<ClientThread> > clientList;
        std::map<WAICCommandType, std::shared_ptr<WAICCommandHandler> > supportedCommands;
    };
}
#endif