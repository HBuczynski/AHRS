#include "ShutdownState.h"

using namespace std;
using namespace communication;

ShutdownState::ShutdownState()
    : AbstractState("ShutdownState")
{ }

ShutdownState::~ShutdownState()
{ }

void ShutdownState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void ShutdownState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
