#include "CalibratedFailedState.h"
#include "ShutdownState.h"
#include "ResetState.h"

#include "ClientUDPManager.h"

using namespace std;
using namespace utility;
using namespace communication;

CalibratedFailedState::CalibratedFailedState()
    : AbstractState("CalibratedFailedState", FeederExternalStateCode::CALIBRATED_FAILED)
{

}

CalibratedFailedState::~CalibratedFailedState()
{

}

void CalibratedFailedState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void CalibratedFailedState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void CalibratedFailedState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void CalibratedFailedState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}


void CalibratedFailedState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void CalibratedFailedState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void CalibratedFailedState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
