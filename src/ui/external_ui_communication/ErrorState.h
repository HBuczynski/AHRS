#ifndef AHRS_ERRORSTATE_H
#define AHRS_ERRORSTATE_H

#include "AbstractState.h"

namespace communication
{
    class ErrorState final : public AbstractState
    {
    public:
        ErrorState();
        ~ErrorState();

        virtual void connectedToServer(CommunicationManagerUI &clientUDPManager) override;
        virtual void redundantProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void masterProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void restartProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void shutdownProcess(CommunicationManagerUI &clientUDPManager) override;
    };
}

#endif