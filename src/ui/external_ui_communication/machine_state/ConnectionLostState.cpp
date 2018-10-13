#include "ConnectionLostState.h"

using namespace std;
using namespace communication;

ConnectionLostState::ConnectionLostState()
    : AbstractState("ConnectionLostState", UIExternalStateCode::CONNECTION_LOST)
{

}

ConnectionLostState::~ConnectionLostState()
{

}

void ConnectionLostState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectionLostState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectionLostState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectionLostState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ConnectionLostState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
