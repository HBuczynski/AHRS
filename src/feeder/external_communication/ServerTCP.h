#ifndef WAIC_SERVER_H
#define WAIC_SERVER_H

#include <interfaces/wireless_commands/Command.h>
#include <logger/Logger.h>
#include <time_manager/TimerInterrupt.h>

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
    class ServerTCP final : public utility::TimerInterruptNotification
    {
    public:
        ServerTCP(uint16_t port, uint8_t maxClientNumber, std::shared_ptr<ClientUDPManager> clientUDPManager);
        ~ServerTCP();

        void startUserActivation();
        void stopUserActivation();


    private:
        void interruptNotification() override;

        void activateUsers();
        void removeUsers();
        void updateClientList();

        uint16_t port_;
        uint8_t maxClientNumber_;

        std::atomic<bool> runUserActivation_;
        std::thread activationThread_;

        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        std::list<std::unique_ptr<ClientThreadTCP> > clientList_;

        utility::TimerInterrupt timerInterrupt_;
        utility::Logger& logger_;

        const uint16_t USER_UPDATE_INTERVAL_MS = 1000;
    };
}
#endif