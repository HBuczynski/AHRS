#ifndef AHRS_REDUNDANTSTATE_H
#define AHRS_REDUNDANTSTATE_H

#include "AbstractState.h"

namespace communication
{
    class RedundantState final : public AbstractState
    {
    public:
        RedundantState();
        ~RedundantState();

        virtual void connectedToServer(CommunicationManagerUI &clientUDPManager) override;
        virtual void redundantProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void masterProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void restartProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void shutdownProcess(CommunicationManagerUI &clientUDPManager) override;
    };
}

#endif