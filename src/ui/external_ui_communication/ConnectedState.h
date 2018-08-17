#ifndef AHRS_CONNECTEDSTATE_H
#define AHRS_CONNECTEDSTATE_H

#include "AbstractState.h"

#include <config_reader/UIParameters.h>

namespace communication
{
    class ConnectedState final : public AbstractState
    {
    public:
        ConnectedState();
        ~ConnectedState();

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;

    private:
        utility::Logger &logger_;
    };
}

#endif