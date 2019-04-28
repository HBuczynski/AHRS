#include "ClientUDPManager.h"

using namespace std;
using namespace utility;
using namespace communication;

ClientUDPManager::ClientUDPManager(const string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
    :   hsm::HSM(name, transitionTable, rootState),
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
        //TODO
        //acceptedUsers();
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

void ClientUDPManager::sendToMainProcess(std::vector<uint8_t>& data)
{
    if(mainProcCallback_)
    {
        mainProcCallback_(data);
    }
}

void ClientUDPManager::registerCallbackToMainProc(std::function<void(std::vector<uint8_t>&)> callback)
{
     mainProcCallback_ = callback;
}

//void ClientUDPManager::startCalibration(const string &planeName, PlaneStatus status)
//{
//    currentState_->startCalibration(*this, planeName, status);
//}

//void ClientUDPManager::startDataSending()
//{
//    currentState_->startDataSending(*this);

//    flightDataManager_->startFlightDataTransmission();
//}

//void ClientUDPManager::stopDataSending()
//{
//    flightDataManager_->stopFlightDataTransmission();
//}
