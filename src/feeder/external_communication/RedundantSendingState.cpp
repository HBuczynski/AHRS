#include "RedundantSendingState.h"

using namespace std;
using namespace communication;

RedundantSendingState::RedundantSendingState()
        : AbstractState("RedundantSendingState", StateCode::REDUNDANT_SENDING)
{

}

RedundantSendingState::~RedundantSendingState()
{

}

void RedundantSendingState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void RedundantSendingState::startCalibration(ClientUDPManager &clientUDPManager, const std::string &planeName, PlaneStatus status) {

}

void RedundantSendingState::calibrationPassed(ClientUDPManager &clientUDPManager) {

}

void RedundantSendingState::calibrationFailed(ClientUDPManager &clientUDPManager) {

}

void RedundantSendingState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void RedundantSendingState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void RedundantSendingState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
