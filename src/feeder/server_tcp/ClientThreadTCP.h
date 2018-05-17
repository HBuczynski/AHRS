#ifndef AHRS_BLACK_BOX_CLIENTTHREADTCP_H
#define AHRS_BLACK_BOX_CLIENTTHREADTCP_H

#include <packet/SendStreamTCP.h>
#include <interfaces/wireless_commands/CommandFactory.h>
#include <feeder/server_tcp/CommandHandlerVisitor.h>
#include <logger/Logger.h>

#include <thread>
#include <atomic>
#include <memory>

namespace communication
{
    class ClientThreadTCP
    {
    public:
        ClientThreadTCP(std::unique_ptr<SendStreamTCP> socket, std::shared_ptr<ClientUDPManager> clientUDPManager);
        ~ClientThreadTCP();

       void initializeCommandHandler();

        void startListen();
        void stopListen();
        bool checkListenEnable();

        void setID(uint32_t id);
        uint32_t getID() const;

    private:
        void runListen();

        std::atomic<bool> runListenThread_;
        std::thread listenThread_;

        std::unique_ptr<SendStreamTCP> socket_;
        uint32_t id_;

        std::shared_ptr<ClientUDPManager> clientUDPManager_;
        CommandFactory commandFactory_;
        CommandHandlerVisitor commandHandler_;

        utility::Logger& logger_;

    };
}
#endif //AHRS_BLACK_BOX_CLIENTTHREADTCP_H
