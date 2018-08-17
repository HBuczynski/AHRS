#ifndef AHRS_ABSTRACTSTATE_H
#define AHRS_ABSTRACTSTATE_H

#include <string>

#include <../../system_states/UIExternalComStates.h>
#include <logger/Logger.h>

namespace communication
{
    class CommunicationManagerUI;

    class AbstractState
    {
    public:
        AbstractState(std::string name, UIExternalStateCode stateCode);
        virtual ~AbstractState();

        virtual void connectedToServer(CommunicationManagerUI &communicationManagerUI) = 0;
        virtual void redundantProcess(CommunicationManagerUI &communicationManagerUI) = 0;
        virtual void masterProcess(CommunicationManagerUI &communicationManagerUI) = 0;
        virtual void restartProcess(CommunicationManagerUI &communicationManagerUI) = 0;
        virtual void shutdownProcess(CommunicationManagerUI &communicationManagerUI) = 0;

        const UIExternalStateCode &getStateCode() const;
        const std::string &getName() const;

    protected:
        void setState(CommunicationManagerUI *machine, AbstractState *state);

        UIExternalStateCode stateCode_;
        const std::string name_;

    };

}

#endif