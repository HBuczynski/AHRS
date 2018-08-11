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
        void startCalibration(ClientUDPManager &clientUDPManager);
        void startDataSending(ClientUDPManager &clientUDPManager);
        void restartProcess(ClientUDPManager &clientUDPManager);
        void shutdownProcess(ClientUDPManager &clientUDPManager);

    };
}

#endif