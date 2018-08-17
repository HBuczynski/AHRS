#include "ShutdownState.h"
#include "ClientUDPManager.h"

using namespace std;
using namespace communication;

ShutdownState::ShutdownState()
    : AbstractState("ShutdownState", FeederExternalStateCode::SHUTDOWN)
{ }

ShutdownState::~ShutdownState()
{ }

void ShutdownState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void ShutdownState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}


void ShutdownState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
