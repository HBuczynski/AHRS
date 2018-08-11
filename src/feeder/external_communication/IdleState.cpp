#include "IdleState.h"

using namespace std;
using namespace communication;

IdleState::IdleState()
    : AbstractState("IdleState")
{ }

IdleState::~IdleState()
{ }

void IdleState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void IdleState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void IdleState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void IdleState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void IdleState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
