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

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;
    };
}

#endif