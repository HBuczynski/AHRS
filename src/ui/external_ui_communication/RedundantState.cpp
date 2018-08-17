#include "RedundantState.h"

using namespace std;
using namespace communication;

RedundantState::RedundantState()
        : AbstractState("RedundantState", UIExternalStateCode::REDUNDANT)
{}

RedundantState::~RedundantState()
{}

void RedundantState::connectedToServer(CommunicationManagerUI &clientUDPManager)
{

}

void RedundantState::redundantProcess(CommunicationManagerUI &clientUDPManager)
{

}

void RedundantState::masterProcess(CommunicationManagerUI &clientUDPManager)
{

}

void RedundantState::restartProcess(CommunicationManagerUI &clientUDPManager)
{

}

void RedundantState::shutdownProcess(CommunicationManagerUI &clientUDPManager)
{

}
