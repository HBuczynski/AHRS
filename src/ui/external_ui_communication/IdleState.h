#ifndef AHRS_IDLESTATE_H
#define AHRS_IDLESTATE_H

#include "AbstractState.h"

namespace communication
{
    class IdleState final : public AbstractState
    {
    public:
        IdleState();
        ~IdleState();

        virtual void connectedToServer(CommunicationManagerUI &clientUDPManager) override;
        virtual void redundantProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void masterProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void restartProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void shutdownProcess(CommunicationManagerUI &clientUDPManager) override;
    };
}

#endif