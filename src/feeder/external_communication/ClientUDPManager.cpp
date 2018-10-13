#include "ClientUDPManager.h"

#include "machine_state/IdleState.h"

using namespace std;
using namespace utility;
using namespace communication;

ClientUDPManager::ClientUDPManager()
    :   currentState_(make_unique<IdleState>()),
        logger_(Logger::getInstance())
{ }

ClientUDPManager::~ClientUDPManager()
{ }

list<pair<shared_ptr<ClientUDP>, uint8_t>> ClientUDPManager::getClientList()
{
    lock_guard<mutex> lock(clientListMutex_);
    return clientList_;
}

void ClientUDPManager::insertNewClient(pair<shared_ptr<ClientUDP>, uint8_t> newClient)
{
    lock_guard<mutex> lock(clientListMutex_);
    clientList_.push_back(newClient);

    if(clientList_.size() == 1)
    {
        acceptedUsers();
    }
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

void ClientUDPManager::setNewState(AbstractState *newState)
{
    if(newState != nullptr)
    {
        currentState_.reset(newState);
    }
    else
    {
        if(logger_.isWarningEnable())
        {
            const string message = string("ClientUDPManager :: Empty state has been forwarded to the state machine.");
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
    }
}

void ClientUDPManager::acceptedUsers()
{
    currentState_->acceptedUsers(*this);
}

void ClientUDPManager::startCalibration(const string &planeName, PlaneStatus status)
{
    currentState_->startCalibration(*this, planeName, status);
}

void ClientUDPManager::startDataSending()
{
    currentState_->startDataSending(*this);
}

void ClientUDPManager::restartProcess()
{
    currentState_->restartProcess(*this);
}

void ClientUDPManager::shutdownProcess()
{
    currentState_->shutdownProcess(*this);
}

const FeederExternalStateCode &ClientUDPManager::getCurrentState() const
{
    return currentState_->getStateCode();
}