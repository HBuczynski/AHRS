#include "RedundantConnectionState.h"

using namespace std;
using namespace communication;

RedundantConnectionState::RedundantConnectionState()
        : AbstractState("RedundantConnectionState", UIExternalStateCode::REDUNDANT)
{}

RedundantConnectionState::~RedundantConnectionState()
{}

void RedundantConnectionState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantConnectionState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantConnectionState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantConnectionState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantConnectionState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
