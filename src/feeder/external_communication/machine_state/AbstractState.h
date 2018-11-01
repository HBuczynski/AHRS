#ifndef AHRS_ABSTRACTSTATE_H
#define AHRS_ABSTRACTSTATE_H

#include <string>
#include <logger/Logger.h>
#include <interfaces/wireless_commands/CallibrateMagnetometerCommand.h>
#include "../../common/FeederStates.h"

namespace communication
{
    class ClientUDPManager;

    class AbstractState
    {
    public:
        AbstractState(std::string name, FeederExternalStateCode stateCode);
        virtual ~AbstractState();

        virtual void acceptedUsers(ClientUDPManager &clientUDPManager) = 0;

        virtual void startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) = 0;
        virtual void calibrationPassed(ClientUDPManager &clientUDPManager) = 0;
        virtual void calibrationFailed(ClientUDPManager &clientUDPManager) = 0;

        virtual void startDataSending(ClientUDPManager &clientUDPManager) = 0;
        virtual void restartProcess(ClientUDPManager &clientUDPManager) = 0;
        virtual void shutdownProcess(ClientUDPManager &clientUDPManager) = 0;

        const FeederExternalStateCode& getStateCode() const;
        const std::string& getName() const;

    protected:
        void setState(ClientUDPManager *machine, AbstractState *state);

        FeederExternalStateCode stateCode_;
        const std::string name_;
        utility::Logger& logger_;
    };

}

#endif
