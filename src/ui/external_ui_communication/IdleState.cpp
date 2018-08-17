#include "IdleState.h"

using namespace std;
using namespace communication;

IdleState::IdleState()
        : AbstractState("IdleState", UIExternalStateCode::IDLE)
{}

IdleState::~IdleState()
{}

void IdleState::connectedToServer(CommunicationManagerUI &clientUDPManager)
{

}

void IdleState::redundantProcess(CommunicationManagerUI &clientUDPManager)
{

}

void IdleState::masterProcess(CommunicationManagerUI &clientUDPManager)
{

}

void IdleState::restartProcess(CommunicationManagerUI &clientUDPManager)
{

}

void IdleState::shutdownProcess(CommunicationManagerUI &clientUDPManager)
{

}