#include "MagnetometerState.h"

using namespace std;
using namespace communication;

MagnetometerState::MagnetometerState()
        : AbstractState("MagnetometerState")
{

}

MagnetometerState::~MagnetometerState()
{

}

void MagnetometerState::acceptedUsers(ClientUDPManager &clientUDPManager) {

}

void MagnetometerState::startCalibration(ClientUDPManager &clientUDPManager) {

}

void MagnetometerState::startDataSending(ClientUDPManager &clientUDPManager) {

}

void MagnetometerState::restartProcess(ClientUDPManager &clientUDPManager) {

}

void MagnetometerState::shutdownProcess(ClientUDPManager &clientUDPManager) {

}
