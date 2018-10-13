#ifndef AHRS_FAILCALIBRATEDSTATE_H
#define AHRS_FAILCALIBRATEDSTATE_H


#include "AbstractState.h"

namespace communication
{
    class CalibratedFailedState : public AbstractState
    {
    public:
        CalibratedFailedState();
        ~CalibratedFailedState();

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