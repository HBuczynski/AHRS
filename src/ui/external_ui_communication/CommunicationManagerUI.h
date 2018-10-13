#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <config_reader/UIParameters.h>
#include <logger/Logger.h>

#include "ServerUDP.h"
#include "ClientTCP.h"
#include "machine_state/AbstractState.h"

namespace communication
{
    class CommunicationManagerUI
    {
    public:
        CommunicationManagerUI(uint8_t processNumber);
        ~CommunicationManagerUI();

        bool initialize();
        void sendCommands(std::unique_ptr<communication::Command> commandIn);

        uint8_t getProcessNumber() const ;

        // Machine state commands:
        void connectedToServer();
        void redundantProcess();
        void masterProcess();
        void restartProcess();
        void shutdownProcess();

        const UIExternalStateCode& getCurrentState() const;
        void setNewState(AbstractState *newState);

    private:

        bool initializeServer();
        bool initializeClientConnection();

        std::unique_ptr<AbstractState> currentState_;

        uint8_t processNumber_;
        config::UIWirelessCommunication wirelessCommunicationParameters_;

        std::unique_ptr<ServerUDP> server_;
        std::unique_ptr<ClientTCP> client_;

        utility::Logger& logger_;
    };
}
#endif