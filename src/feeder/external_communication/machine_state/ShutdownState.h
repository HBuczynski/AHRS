#ifndef AHRS_SHUTDOWNSTATE_H
#define AHRS_SHUTDOWNSTATE_H

#include "AbstractState.h"

namespace communication
{
    class ShutdownState : public AbstractState
    {
    public:
        ShutdownState();
        ~ShutdownState();

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
