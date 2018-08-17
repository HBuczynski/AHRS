#ifndef AHRS_IDLESTATE_H
#define AHRS_IDLESTATE_H

#include "AbstractState.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class IdleState final : public AbstractState
    {
    public:
        IdleState();
        ~IdleState();

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) override;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) override;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) override;

    private:
        config::UICommunicationSystemParameters uiCommunicationSystemParameters_;
        utility::Logger &logger_;
    };
}

#endif