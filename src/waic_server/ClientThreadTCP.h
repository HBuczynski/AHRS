#ifndef AHRS_BLACK_BOX_CLIENTTHREADTCP_H
#define AHRS_BLACK_BOX_CLIENTTHREADTCP_H

#include <waic_packet/SendStreamTCP.h>
#include <waic_protocol/CommandFactory.h>
#include <waic_protocol/CommandHandlerVisitor.h>
#include <waic_communication_manager/CallbackFunctions.h>

#include <thread>
#include <atomic>
#include <memory>

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
        CommandHandlerVisitor commandHandler_;

    };
}
#endif //AHRS_BLACK_BOX_CLIENTTHREADTCP_H
