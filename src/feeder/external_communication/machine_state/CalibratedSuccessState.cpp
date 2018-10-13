#include <config_reader/FeederParameters.h>
#include <config_reader/ConfigurationReader.h>
#include "CalibratedSuccessState.h"
#include "ClientUDPManager.h"

#include "ShutdownState.h"
#include "ResetState.h"
#include "RedundantSendingState.h"
#include "MasterSendingState.h"

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;

CalibratedSuccessState::CalibratedSuccessState()
    : AbstractState("CalibratedSuccessState", FeederExternalStateCode::CALIBRATED_SUCCESS)
{ }

CalibratedSuccessState::~CalibratedSuccessState()
{ }

void CalibratedSuccessState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void CalibratedSuccessState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void CalibratedSuccessState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void CalibratedSuccessState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}

void CalibratedSuccessState::startDataSending(ClientUDPManager &clientUDPManager)
{
    const auto feederParam = ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH);

    //TODO: make appropriate action

    switch(feederParam.mode)
    {
        case FeederMode::MASTER : {
            setState(&clientUDPManager, new MasterSendingState());

            if (logger_.isInformationEnable()) {
                const string message = string("RegisteredUsersState :: Change state on MasterSendingState");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
            break;
        }
        case FeederMode::REDUNDANT : {
            setState(&clientUDPManager, new RedundantSendingState());

            if (logger_.isInformationEnable()) {
                const string message = string("RegisteredUsersState :: Change state on RedundantSendingState");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
            break;
        }
        default:
        {
            if (logger_.isErrorEnable()) {
                const string message = string("RegisteredUsersState :: Wrong FeederMode.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
            break;
        }

    }
}

void CalibratedSuccessState::restartProcess(ClientUDPManager &clientUDPManager)
{

}

void CalibratedSuccessState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
