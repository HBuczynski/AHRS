#include "CommunicationManagerBlackBox.h"

#include <iostream>

using namespace std;
using namespace communication;

CommunicationManagerBlackBox::CommunicationManagerBlackBox(uint16_t serverPort, uint8_t maxUserNumber)
{
    server_ = make_shared<ServerTCP>(serverPort, maxUserNumber, this);

    initialize();
}

CommunicationManagerBlackBox::~CommunicationManagerBlackBox()
{
}


void CommunicationManagerBlackBox::initialize()
{
    activateServer();
}

void CommunicationManagerBlackBox::activateServer()
{
    server_->startUserActivation();
}

const list<pair<shared_ptr<ClientUDP>, uint8_t>> & CommunicationManagerBlackBox::getClientList()
{
    lock_guard<mutex> lock(clientListMutex_);
    return clientList_;
}

void CommunicationManagerBlackBox::insertNewClient(pair<shared_ptr<ClientUDP>, uint8_t> newClient)
{
    lock_guard<mutex> lock(clientListMutex_);
    clientList_.push_back(newClient);
}

void CommunicationManagerBlackBox::removeClient(uint8_t id)
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


