#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <config_reader/UIParameters.h>
#include <logger/Logger.h>

#include "ServerUDP.h"
#include "ClientTCP.h"

namespace communication
{
    class CommunicationManagerUI
    {
    public:
        CommunicationManagerUI(uint8_t processNumber);
        ~CommunicationManagerUI();

        bool initialize();
        void sendCommands(std::unique_ptr<communication::Command> commandIn);

    private:

        bool initializeServer();
        bool initializeClientConnection();

        uint8_t processNumber_;
        config::UIWirelessCommunication wirelessCommunicationParameters_;

        std::unique_ptr<ServerUDP> server_;
        std::unique_ptr<ClientTCP> client_;

        utility::Logger& logger_;
    };
}
#endif