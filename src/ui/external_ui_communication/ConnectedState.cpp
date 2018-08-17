#include "ConnectedState.h"

using namespace std;
using namespace communication;

ConnectedState::ConnectedState()
    : AbstractState("ConnectedState", UIExternalStateCode::CONNECTED)
{}

ConnectedState::~ConnectedState()
{}

void ConnectedState::connectedToServer(CommunicationManagerUI &clientUDPManager)
{

}

void ConnectedState::redundantProcess(CommunicationManagerUI &clientUDPManager)
{

}

void ConnectedState::masterProcess(CommunicationManagerUI &clientUDPManager)
{

}

void ConnectedState::restartProcess(CommunicationManagerUI &clientUDPManager)
{

}

void ConnectedState::shutdownProcess(CommunicationManagerUI &clientUDPManager)
{

}
