#include "CommunicationManager.h"

#include <iostream>

using namespace std;
using namespace communication;

CommunicationManager::CommunicationManager(CommunicationParameters parameters)
    : parameters_(parameters)
{
    server_ = make_unique<Server>(parameters_.sourcePortUDP);
    client_ = make_unique<Client>(parameters_.destinationPortTCP, parameters_.destinationAddressTCP);
}

CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::initializeServer()
{
    server_->startListening();
}

void CommunicationManager::initializeClientConnection()
{
    client_->connectToServer();
    // to do: exception
    client_->startCommandSending();
}

void CommunicationManager::sendCommands()
{
    
}



