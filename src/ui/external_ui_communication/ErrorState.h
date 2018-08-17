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

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;
    };
}

#endif