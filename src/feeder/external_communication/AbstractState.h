#ifndef AHRS_ABSTRACTSTATE_H
#define AHRS_ABSTRACTSTATE_H

#include <string>
#include <logger/Logger.h>

#include "CommunicationEventInterface.h"

namespace communication
{
    class ClientUDPManager;

    class AbstractState : public CommunicationEventInterface
    {
    public:
        AbstractState(std::string name);
        virtual ~AbstractState();

        virtual void acceptedUsers(ClientUDPManager &clientUDPManager) = 0;
        virtual void startCalibration(ClientUDPManager &clientUDPManager) = 0;
        virtual void startDataSending(ClientUDPManager &clientUDPManager) = 0;
        virtual void restartProcess(ClientUDPManager &clientUDPManager) = 0;
        virtual void shutdownProcess(ClientUDPManager &clientUDPManager) = 0;

        const std::string& getName() const;

    protected:
        void setState(ClientUDPManager *machine, AbstractState *state);

        const std::string name_;
        utility::Logger& logger_;
    };

}

#endif
