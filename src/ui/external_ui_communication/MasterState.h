#ifndef AHRS_MASTERSTATE_H
#define AHRS_MASTERSTATE_H

#include "AbstractState.h"

namespace communication
{
    class MasterState final : public AbstractState
    {
    public:
        MasterState();
        ~MasterState();

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;
    };
}


#endif