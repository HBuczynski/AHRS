#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include <interfaces/wireless_commands/Command.h>
#include <logger/Logger.h>

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
    class ServerTCP
    {
    public:
        ServerTCP(uint16_t port, uint8_t maxClientNumber, std::shared_ptr<ClientUDPManager> clientUDPManager);
        ~ServerTCP();

        void startUserActivation();
        void stopUserActivation();
        void removeUsers();

        void startDataSending();
        void stopDataSending();

    private:
        void activateUsers();
        void updateClientList();

        uint16_t port_;
        uint8_t maxClientNumber_;

        std::atomic<bool> runUserActivation_;
        std::thread activationThread_;

        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        std::list<std::unique_ptr<ClientThreadTCP> > clientList_;

        utility::Logger& logger_;
    };
}
#endif