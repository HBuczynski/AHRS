#ifndef AHRS_CONNECTEDSTATE_H
#define AHRS_CONNECTEDSTATE_H

#include "AbstractState.h"

namespace communication
{
    class ConnectedState final : public AbstractState
    {
    public:
        ConnectedState();
        ~ConnectedState();

        virtual void connectedToServer(CommunicationManagerUI &clientUDPManager) override;
        virtual void redundantProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void masterProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void restartProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void shutdownProcess(CommunicationManagerUI &clientUDPManager) override;
    };
}

#endif