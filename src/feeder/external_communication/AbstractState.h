#ifndef AHRS_ABSTRACTSTATE_H
#define AHRS_ABSTRACTSTATE_H

#include <string>
#include <logger/Logger.h>
#include <interfaces/wireless_commands/CallibrateMagnetometerCommand.h>

namespace communication
{
    class ClientUDPManager;

    enum class StateCode : uint8_t
    {
        IDLE = 0x01,
        CALIBRATING = 0x02,
        ERROR = 0x03,
        CALIBRATED_FAILED = 0x04,
        MASTER_SENDING = 0x05,
        REDUNDANT_SENDING = 0x06,
        REGISTERED_USERS = 0x07,
        RESET = 0x08,
        SHUTDOWN = 0x09,
        CALIBRATED_SUCCESS= 0x10
    };

    class AbstractState
    {
    public:
        AbstractState(std::string name, StateCode stateCode);
        virtual ~AbstractState();

        virtual void acceptedUsers(ClientUDPManager &clientUDPManager) = 0;

        virtual void startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) = 0;
        virtual void calibrationPassed(ClientUDPManager &clientUDPManager) = 0;
        virtual void calibrationFailed(ClientUDPManager &clientUDPManager) = 0;

        virtual void startDataSending(ClientUDPManager &clientUDPManager) = 0;
        virtual void restartProcess(ClientUDPManager &clientUDPManager) = 0;
        virtual void shutdownProcess(ClientUDPManager &clientUDPManager) = 0;

        const StateCode& getStateCode() const;
        const std::string& getName() const;

    protected:
        void setState(ClientUDPManager *machine, AbstractState *state);

        StateCode stateCode_;
        const std::string name_;
        utility::Logger& logger_;
    };

}

#endif
