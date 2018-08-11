#include "MasterSendingState.h"

using namespace std;
using namespace communication;

MasterSendingState::MasterSendingState()
    : AbstractState("MasterSendingState", StateCode::MASTER_SENDING)
{

}

MasterSendingState::~MasterSendingState()
{

}

void MasterSendingState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void MasterSendingState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
