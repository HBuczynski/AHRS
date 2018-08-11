#ifndef AHRS_MAGNETOMETERSTATE_H
#define AHRS_MAGNETOMETERSTATE_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include <config_reader/FeederParameters.h>

#include "AbstractState.h"

namespace communication
{
    class CalibratingState : public AbstractState
    {
    public:
        CalibratingState();
        ~CalibratingState();

        void acceptedUsers(ClientUDPManager &clientUDPManager);
        void startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status);
        void calibrationPassed(ClientUDPManager &clientUDPManager);
        void calibrationFailed(ClientUDPManager &clientUDPManager);
        void startDataSending(ClientUDPManager &clientUDPManager);
        void restartProcess(ClientUDPManager &clientUDPManager);
        void shutdownProcess(ClientUDPManager &clientUDPManager);

    private:
        void initializeMessageQueue();

        config::FeederMessageQueues messageQueuesParameters_;
        std::shared_ptr<boost::interprocess::message_queue> mainMessageQueue;
    };
}

#endif
