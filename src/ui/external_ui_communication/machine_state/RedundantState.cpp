#include "RedundantState.h"

using namespace std;
using namespace communication;

RedundantState::RedundantState()
        : AbstractState("RedundantState", UIExternalStateCode::REDUNDANT)
{}

RedundantState::~RedundantState()
{}

void RedundantState::connectedToServer(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantState::redundantProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantState::masterProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantState::restartProcess(CommunicationManagerUI &communicationManagerUI)
{

}

void RedundantState::shutdownProcess(CommunicationManagerUI &communicationManagerUI)
{

}
