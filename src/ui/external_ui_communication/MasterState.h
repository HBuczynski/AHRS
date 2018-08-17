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

        virtual void connectedToServer(CommunicationManagerUI &clientUDPManager) override;
        virtual void redundantProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void masterProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void restartProcess(CommunicationManagerUI &clientUDPManager) override;
        virtual void shutdownProcess(CommunicationManagerUI &clientUDPManager) override;
    };
}


#endif