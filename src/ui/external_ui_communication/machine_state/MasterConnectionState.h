#ifndef AHRS_MASTERSTATE_H
#define AHRS_MASTERSTATE_H

#include "AbstractState.h"

namespace communication
{
    class MasterConnectionState final : public AbstractState
    {
    public:
        MasterConnectionState();
        ~MasterConnectionState();

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;
    };
}


#endif