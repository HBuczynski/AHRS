#ifndef AHRS_IDLESTATE_H
#define AHRS_IDLESTATE_H

#include "AbstractState.h"

namespace communication
{
    class IdleState : public AbstractState
    {
    public:
        IdleState();
        ~IdleState();

        void acceptedUsers(ClientUDPManager &clientUDPManager);
        void startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status);
        void calibrationPassed(ClientUDPManager &clientUDPManager);
        void calibrationFailed(ClientUDPManager &clientUDPManager);
        void startDataSending(ClientUDPManager &clientUDPManager);
        void restartProcess(ClientUDPManager &clientUDPManager);
        void shutdownProcess(ClientUDPManager &clientUDPManager);
    };
}

#endif