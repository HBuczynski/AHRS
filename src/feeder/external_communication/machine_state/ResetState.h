#ifndef AHRS_RESETSTATE_H
#define AHRS_RESETSTATE_H

#include "AbstractState.h"

namespace communication
{
    class ResetState  : public AbstractState
    {
    public:
        ResetState();
        ~ResetState();

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