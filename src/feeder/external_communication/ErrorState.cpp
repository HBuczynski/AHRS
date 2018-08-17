#include "ErrorState.h"
#include "ClientUDPManager.h"

using namespace std;
using namespace communication;

ErrorState::ErrorState()
    : AbstractState("ErrorState", FeederExternalStateCode::ERROR)
{

}

ErrorState::~ErrorState()
{

}

void ErrorState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void ErrorState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void ErrorState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void ErrorState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}

void ErrorState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void ErrorState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void ErrorState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}


