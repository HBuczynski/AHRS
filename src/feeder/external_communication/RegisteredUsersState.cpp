#include "RegisteredUsersState.h"

using namespace std;
using namespace communication;

RegisteredUsersState::RegisteredUsersState()
    : AbstractState("ErrorState")
{

}

RegisteredUsersState::~RegisteredUsersState()
{

}

void RegisteredUsersState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void RegisteredUsersState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void RegisteredUsersState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void RegisteredUsersState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void RegisteredUsersState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
