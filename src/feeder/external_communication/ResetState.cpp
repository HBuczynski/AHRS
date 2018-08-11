#include "ResetState.h"
#include "ClientUDPManager.h"

using namespace std;
using namespace communication;

ResetState::ResetState()
    : AbstractState("ResetState", StateCode::RESET)
{

}

ResetState::~ResetState()
{

}

void ResetState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void ResetState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void ResetState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void ResetState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}

void ResetState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void ResetState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void ResetState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
