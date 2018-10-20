#include "MasterConnectionState.h"

using namespace std;
using namespace communication;

MasterConnectionState::MasterConnectionState()
        : AbstractState("MasterConnectionState", UIExternalStateCode::MASTER)
{}

MasterConnectionState::~MasterConnectionState()
{}

void MasterConnectionState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterConnectionState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterConnectionState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterConnectionState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void MasterConnectionState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
