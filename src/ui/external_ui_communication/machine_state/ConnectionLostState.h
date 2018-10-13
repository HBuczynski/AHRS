#ifndef AHRS_CONNECTIONLOSTSTATE_H
#define AHRS_CONNECTIONLOSTSTATE_H

#include "AbstractState.h"

#include <config_reader/UIParameters.h>

namespace communication
{
    class ConnectionLostState final : public AbstractState
    {
    public:
        ConnectionLostState();
        ~ConnectionLostState();

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;
    };
}


#endif