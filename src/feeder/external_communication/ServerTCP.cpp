#include "ServerTCP.h"

#include <interfaces/wireless_commands/Command.h>
#include <interfaces/wireless_responses/Response.h>
#include <packet/ListenStreamTCP.h>

#include <algorithm>


#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

ServerTCP::ServerTCP(uint16_t port,  uint8_t maxClientNumber, shared_ptr<ClientUDPManager> clientUDPManager)
        : port_(port),
          maxClientNumber_(maxClientNumber),
          runUserActivation_(false),
          clientUDPManager_(clientUDPManager),
          logger_(Logger::getInstance())
{ }

ServerTCP::~ServerTCP()
{
    timerInterrupt_.stop();
    stopUserActivation();
    removeUsers();
}

void ServerTCP::startUserActivation()
{
    runUserActivation_ = true;

    activationThread_ = thread(&ServerTCP::activateUsers, this);
    timerInterrupt_.startPeriodic(USER_UPDATE_INTERVAL_MS, this);
}

void ServerTCP::interruptNotification(timer_t timerID)
{
    updateClientList();
}

void ServerTCP::stopUserActivation()
{
    runUserActivation_ = false;

    if(activationThread_.joinable())
    {
        activationThread_.join();
    }
}

void ServerTCP::activateUsers()
{
    ListenStreamTCP serverSocket(port_);

    serverSocket.listenUsers(maxClientNumber_);
    uint32_t clientID = 1;

    if(logger_.isInformationEnable())
    {
        const string message = string("-EXTCOM- ServerTCP :: Server starts user acceptance.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    while(runUserActivation_)
    {
        updateClientList();

        if(clientList_.size() < maxClientNumber_)
        {
            //Wait on new users.
            auto client = make_unique<ClientThreadTCP>(move(serverSocket.acceptUsers()),clientUDPManager_);

            if(logger_.isInformationEnable())
            {
                const string message = string("-EXTCOM- ServerTCP :: Client with ID -") + to_string(clientID) + string("- was registered.");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }
            client->setID(clientID);
            client->startListen();

            //Assign new client_udp to the vector.
            clientList_.push_back(move(client));
            ++clientID;
        }
        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void ServerTCP::updateClientList()
{
    bool isSuccess = false;

    for(auto iter = clientList_.begin(); (iter != clientList_.end() && !isSuccess); ++iter)
    {
        if(!(*iter)->checkListenEnable())
        {
            if(logger_.isInformationEnable())
            {
                const string message = string("-EXTCOM- ServerTCP :: Client with ID -") + to_string((*iter)->getID()) + string("- was removed.");
                logger_.writeLog(LogType::INFORMATION_LOG, message);
            }

            const auto id = (*iter)->getID();
            clientList_.erase(iter);
            clientUDPManager_->removeClient(id);

            isSuccess = true;
        }
    }
}

void ServerTCP::removeUsers()
{
    for(auto iter = clientList_.begin(); iter != clientList_.end(); ++iter)
    {
        (*iter)->stopListen();
        clientList_.erase(iter);
    }
}
