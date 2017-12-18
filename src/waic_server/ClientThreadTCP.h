#ifndef AHRS_BLACK_BOX_CLIENTTHREADTCP_H
#define AHRS_BLACK_BOX_CLIENTTHREADTCP_H

#include <waic_client/Client.h>
#include <waic_packet/SendStreamTCP.h>
#include <waic_protocol/CommandFactory.h>
#include <waic_protocol/CommandHandler.h>
#include <waic_communication_manager/CallbackFunctions.h>

#include <thread>
#include <atomic>
#include <atomic>
#include <memory>
#include <list>
#include <utility>

namespace communication
{
    class ClientThreadTCP
    {
    public:
        ClientThreadTCP(std::unique_ptr<SendStreamTCP> socket, CallbackFunctions callbackFunctions);
        ~ClientThreadTCP();

        void initializeCommandHandler();

        void startListen();
        void stopListen();
        bool checkListenEnable();

        void setID(uint32_t id);
        uint32_t getID();

    private:
        void runListen();

        std::atomic<bool> runListenThread_;
        std::thread listenThread_;

        std::unique_ptr<SendStreamTCP> socket_;
        uint32_t id_;

        CallbackFunctions callbackFunctions_;
        CommandFactory commandFactory_;
        CommandHandler commandHandler_;

    };
}
#endif //AHRS_BLACK_BOX_CLIENTTHREADTCP_H
