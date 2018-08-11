#include "ResetState.h"

using namespace std;
using namespace communication;

ResetState::ResetState()
    : AbstractState("ResetState")
{

}

ResetState::~ResetState()
{

}

void ResetState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void ResetState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void ResetState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void ResetState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void ResetState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
