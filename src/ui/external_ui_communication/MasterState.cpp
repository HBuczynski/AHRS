#include "MasterState.h"

using namespace std;
using namespace communication;

MasterState::MasterState()
        : AbstractState("MasterState", UIExternalStateCode::MASTER)
{}

MasterState::~MasterState()
{}

void MasterState::connectedToServer(CommunicationManagerUI &clientUDPManager)
{

}

void MasterState::redundantProcess(CommunicationManagerUI &clientUDPManager)
{

}

void MasterState::masterProcess(CommunicationManagerUI &clientUDPManager)
{

}

void MasterState::restartProcess(CommunicationManagerUI &clientUDPManager)
{

}

void MasterState::shutdownProcess(CommunicationManagerUI &clientUDPManager)
{

}
