#include "ClientUDPManager.h"

using namespace std;
using namespace communication;

ClientUDPManager::ClientUDPManager()
{

}

ClientUDPManager::~ClientUDPManager()
{

}

list<pair<shared_ptr<ClientUDP>, uint8_t>> ClientUDPManager::getClientList()
{
    lock_guard<mutex> lock(clientListMutex_);
    return clientList_;
}

void ClientUDPManager::insertNewClient(pair<shared_ptr<ClientUDP>, uint8_t> newClient)
{
    lock_guard<mutex> lock(clientListMutex_);
    clientList_.push_back(newClient);
}

void ClientUDPManager::removeClient(uint8_t id)
{
    lock_guard<mutex> lock(clientListMutex_);
    if(!clientList_.empty())
    {
        bool isSuccess = false;
        for (auto iter = clientList_.begin(); (iter != clientList_.end()) & !isSuccess; ++iter)
        {
            if ((*iter).second == id)
            {
                clientList_.erase(iter);
                isSuccess = true;
            }
        }
    }
}

void ClientUDPManager::broadcast(vector<uint8_t> frame)
{
    lock_guard<mutex> lock(clientListMutex_);
    for(const auto& client : clientList_)
    {
        client.first->sendData(frame);
    }
}

