#include "CommunicationManager.h"

#include <iostream>

using namespace std;
using namespace communication;

CommunicationManager::CommunicationManager(uint16_t serverPort, uint8_t maxUserNumber)
{
    server_ = make_shared<Server>(serverPort, maxUserNumber, this);

    initialize();
}

CommunicationManager::~CommunicationManager()
{
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

