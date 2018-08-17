#include "ErrorState.h"

using namespace std;
using namespace communication;

ErrorState::ErrorState()
        : AbstractState("ErrorState", UIExternalStateCode::ERROR)
{}

ErrorState::~ErrorState()
{}

void ErrorState::connectedToServer(CommunicationManagerUI &clientUDPManager)
{

}

void ErrorState::redundantProcess(CommunicationManagerUI &clientUDPManager)
{

}

void ErrorState::masterProcess(CommunicationManagerUI &clientUDPManager)
{

}

void ErrorState::restartProcess(CommunicationManagerUI &clientUDPManager)
{

}

void ErrorState::shutdownProcess(CommunicationManagerUI &clientUDPManager)
{

}
