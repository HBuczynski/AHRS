#ifndef AHRS_REDUNDANTSENDINGSTATE_H
#define AHRS_REDUNDANTSENDINGSTATE_H

#include "AbstractState.h"

namespace communication
{
    class RedundantSendingState  : public AbstractState
    {
    public:
        RedundantSendingState();
        ~RedundantSendingState();

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
