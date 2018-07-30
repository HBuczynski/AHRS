#include "ProcessManager.h"

#include <iostream>

using namespace std;
using namespace communication;

ProcessManager::ProcessManager(uint16_t serverPort, uint8_t maxUserNumber)
{
    clientUDPManager_ = make_shared<ClientUDPManager>();
    server_ = make_shared<ServerTCP>(serverPort, maxUserNumber, clientUDPManager_);
}

ProcessManager::~ProcessManager()
{ }

void ProcessManager::initializeExternalCommmunication()
{
    server_->startUserActivation();
}

void ProcessManager::initializeMessageQueueCommunication()
{

}

void ProcessManager::initializeSharedMemoryCommunication()
{

}




