#include "CommunicationManager.h"

#include "InitConnectionExecutor.h"
#include "EndConnectionExecutor.h"


#include <iostream>

using namespace std;
using namespace communication;

CommunicationManager::CommunicationManager(uint16_t serverPort, uint8_t maxUserNumber)
{
    server_ = make_shared<Server>(serverPort, maxUserNumber);

    initialize();
}

CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::initialize()
{
    callbackFunctions_.getClientList = bind(&CommunicationManager::getClientList, this); // zamienić na lambdy
    callbackFunctions_.insertNewClient = bind(&CommunicationManager::insertNewClient, this, std::placeholders::_1);
    callbackFunctions_.removeClient = bind(&CommunicationManager::removeClient, this, std::placeholders::_1);

    server_->initializeHandlers(callbackFunctions_);
}

void CommunicationManager::activateServer()
{
    server_->startUserActivation();
}

const list<pair<shared_ptr<Client>, uint8_t>> & CommunicationManager::getClientList()
{
    lock_guard<mutex> lock(clientListMutex_);
    return clientList_;
}

void CommunicationManager::insertNewClient(pair<shared_ptr<Client>, uint8_t> newClient)
{
    lock_guard<mutex> lock(clientListMutex_);
    clientList_.push_back(newClient);
}

void CommunicationManager::removeClient(uint8_t id)
{
    lock_guard<mutex> lock(clientListMutex_);

    for(auto iter = clientList_.begin(); iter != clientList_.end(); ++iter)
    {
        if((*iter).second == id)
        {
            clientList_.erase(iter);
        }
    }
}

