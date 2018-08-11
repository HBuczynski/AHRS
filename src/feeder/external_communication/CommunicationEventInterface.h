#ifndef AHRS_STATEINTERFACE_H
#define AHRS_STATEINTERFACE_H

namespace communication
{
    class ClientUDPManager;

    class CommunicationEventInterface
    {
    public:
        CommunicationEventInterface() { };
        virtual ~CommunicationEventInterface() { };

        virtual void acceptedUsers(ClientUDPManager &clientUDPManager) = 0;
        virtual void startCalibration(ClientUDPManager &clientUDPManager) = 0;
        virtual void startDataSending(ClientUDPManager &clientUDPManager) = 0;
        virtual void restartProcess(ClientUDPManager &clientUDPManager) = 0;
        virtual void shutdownProcess(ClientUDPManager &clientUDPManager) = 0;
    };
}

#endif
