#include "ErrorState.h"

using namespace std;
using namespace communication;

ErrorState::ErrorState()
        : AbstractState("ErrorState", UIExternalStateCode::ERROR)
{}

ErrorState::~ErrorState()
{}

void ErrorState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void ErrorState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ErrorState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ErrorState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void ErrorState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
