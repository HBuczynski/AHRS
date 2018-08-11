#include "MasterSendingState.h"

using namespace std;
using namespace communication;

MasterSendingState::MasterSendingState()
    : AbstractState("MasterSendingState")
{

}

MasterSendingState::~MasterSendingState()
{

}

void MasterSendingState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void MasterSendingState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
