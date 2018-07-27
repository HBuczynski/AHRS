#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include "../../config_reader/ConfigurationReader.h"
#include "ServerUDP.h"
#include "ClientTCP.h"

#include "../../../../../../../../usr/include/c++/5/memory"
#include "../../../../../../../../usr/include/c++/5/list"
#include "../../../../../../../../usr/include/c++/5/utility"
#include "../../../../../../../../usr/include/c++/5/mutex"
#include "../../../../../../../../usr/include/c++/5/memory"
#include "../../../../../../../../usr/include/c++/5/string"

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