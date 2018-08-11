#ifndef AHRS_REGISTEREDUSERSSTATE_H
#define AHRS_REGISTEREDUSERSSTATE_H

#include "AbstractState.h"

namespace communication
{
    class RegisteredUsersState : public AbstractState
    {
    public:
        RegisteredUsersState();
        ~RegisteredUsersState();

        void acceptedUsers(ClientUDPManager &clientUDPManager);
        void startCalibration(ClientUDPManager &clientUDPManager);
        void startDataSending(ClientUDPManager &clientUDPManager);
        void restartProcess(ClientUDPManager &clientUDPManager);
        void shutdownProcess(ClientUDPManager &clientUDPManager);

    };
}

#endif
