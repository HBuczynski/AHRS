#include "CommunicationManager.h"

#include <iostream>

using namespace std;
using namespace communication;

CommunicationManager::CommunicationManager(uint16_t serverPort, uint8_t maxUserNumber)
{
    clientUDPManager_ = make_shared<ClientUDPManager>();
    server_ = make_shared<ServerTCP>(serverPort, maxUserNumber, clientUDPManager_);
}

CommunicationManager::~CommunicationManager()
{ }

void CommunicationManager::initializeExternalCommmunication()
{
    server_->startUserActivation();
}

void CommunicationManager::initializeMessageQueueCommunication()
{

}

void CommunicationManager::initializeSharedMemoryCommunication()
{

}




