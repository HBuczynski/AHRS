#ifndef AHRS_SUCCESSFULCALIBRATEDSTATE_H
#define AHRS_SUCCESSFULCALIBRATEDSTATE_H

#include "AbstractState.h"

namespace communication
{
    class CalibratedSuccessState : public AbstractState
    {
    public:
        CalibratedSuccessState();
        ~CalibratedSuccessState();

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
