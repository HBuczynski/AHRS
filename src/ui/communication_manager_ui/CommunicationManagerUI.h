#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <ui/server_udp/ServerUDP.h>
#include <ui/client_tcp/ClientTCP.h>

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

    class CommunicationManagerUI
    {
    public:
        CommunicationManagerUI(CommunicationParameters parameters);
        ~CommunicationManagerUI();

        void initializeServer();
        void initializeClientConnection();

        void sendCommands();

    private:
        CommunicationParameters parameters_;

        std::unique_ptr<ServerUDP> server_;
        std::unique_ptr<ClientTCP> client_;
    };
}
#endif