#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <config_reader/ConfigurationReader.h>
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
    class CommunicationManagerUI
    {
    public:
        CommunicationManagerUI();
        ~CommunicationManagerUI();

        void sendCommands(std::unique_ptr<communication::Command> commandIn);

    private:
        void initializeServer();
        void initializeClientConnection();

        config::CommunicationParameters parameters_;

        std::unique_ptr<ServerUDP> server_;
        std::unique_ptr<ClientTCP> client_;
    };
}
#endif