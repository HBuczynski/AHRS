#include "MasterState.h"

using namespace std;
using namespace communication;

MasterState::MasterState()
        : AbstractState("MasterState", UIExternalStateCode::MASTER)
{}

MasterState::~MasterState()
{}

void MasterState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
