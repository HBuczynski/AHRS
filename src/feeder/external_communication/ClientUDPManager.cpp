#include "ClientUDPManager.h"

#include "machine_state/IdleState.h"

using namespace std;
using namespace utility;
using namespace communication;

ClientUDPManager::ClientUDPManager()
    :   currentState_(make_unique<IdleState>()),
        flightDataManager_(make_unique<FlightDataManager>(bind(&ClientUDPManager::broadcast, this, std::placeholders::_1))),
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

bool ClientUDPManager::broadcast(vector<uint8_t> frame)
{
    lock_guard<mutex> lock(clientListMutex_);

    if(clientList_.empty())
    {
        return false;
    }

    for(const auto& client : clientList_)
    {
        client.first->sendData(frame);
    }

    return true;
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
    if(logger_.isWarningEnable())
    {
        const string message = string("ClientUDPManager ::acceptedUsers.");
        logger_.writeLog(LogType::WARNING_LOG, message);
    }

    currentState_->acceptedUsers(*this);
}

void ClientUDPManager::startCalibration(const string &planeName, PlaneStatus status)
{
    currentState_->startCalibration(*this, planeName, status);
}

void ClientUDPManager::startDataSending()
{
    currentState_->startDataSending(*this);

    flightDataManager_->startFlightDataTransmission();
}

void ClientUDPManager::stopDataSending()
{
    flightDataManager_->stopFlightDataTransmission();
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
