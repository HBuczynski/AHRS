#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <ahrs_ui/server_udp/ServerUDP.h>
#include <ahrs_ui/client_tcp/ClientTCP.h>

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

    class CommunicationManagerUI :  public  ResponseNotification
    {
    public:
        CommunicationManagerUI(CommunicationParameters parameters);
        ~CommunicationManagerUI();

        virtual void received(std::vector<uint8_t > responseFrame) override;

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