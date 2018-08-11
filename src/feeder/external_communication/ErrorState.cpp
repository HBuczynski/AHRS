#include "ErrorState.h"

using namespace std;
using namespace communication;

ErrorState::ErrorState()
    : AbstractState("ErrorState")
{

}

ErrorState::~ErrorState()
{

}

void ErrorState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void ErrorState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void ErrorState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void ErrorState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void ErrorState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
