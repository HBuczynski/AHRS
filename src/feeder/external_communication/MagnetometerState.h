#ifndef AHRS_MAGNETOMETERSTATE_H
#define AHRS_MAGNETOMETERSTATE_H

#include "AbstractState.h"

namespace communication {

    class MagnetometerState : public AbstractState
    {
    public:
        MagnetometerState();
        ~MagnetometerState();

        void acceptedUsers(ClientUDPManager &clientUDPManager);
        void startCalibration(ClientUDPManager &clientUDPManager);
        void startDataSending(ClientUDPManager &clientUDPManager);
        void restartProcess(ClientUDPManager &clientUDPManager);
        void shutdownProcess(ClientUDPManager &clientUDPManager);

    };
}

#endif
