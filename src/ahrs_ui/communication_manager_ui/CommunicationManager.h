#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <ahrs_ui/server_udp/Server.h>
#include <ahrs_ui/client_tcp/Client.h>

#include <memory>
#include <list>
#include <utility>
#include <mutex>
#include <memory>
#include <string>

namespace communication
{
    struct CommunicationParameters
    {
        uint16_t sourcePortUDP;
        std::string sourceAddressUDP;

        uint16_t destinationPortTCP;
        std::string destinationAddressTCP;
    };

    class CommunicationManager
    {
    public:
        CommunicationManager(CommunicationParameters parameters);
        ~CommunicationManager();

        void initializeServer();
        void initializeClientConnection();

        void sendCommands();

    private:
        CommunicationParameters parameters_;

        std::unique_ptr<Server> server_;
        std::unique_ptr<Client> client_;
    };
}
#endif