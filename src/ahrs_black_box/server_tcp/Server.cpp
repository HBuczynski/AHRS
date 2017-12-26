#include "Server.h"

#include <protocol/Command.h>
#include <protocol/Response.h>
#include <packet/ListenStreamTCP.h>

#include <algorithm>

using namespace std;
using namespace communication;

Server::Server(uint16_t port,  uint8_t maxClientNumber, ClientUDPManager *clientUDPManager)
        : port_(port),
          maxClientNumber_(maxClientNumber),
          clientUDPManager_(clientUDPManager),
          runUserActivation_(false)
{ }

Server::~Server()
{
    stopUserActivation();

    if(activationThread_.joinable())
    {
        activationThread_.join();
    }
}

void Server::startUserActivation()
{
    runUserActivation_ = true;

    activationThread_ = thread(&Server::activateUsers, this);
}

void Server::stopUserActivation()
{
    runUserActivation_ = false;
}

void Server::activateUsers()
{
    ListenStreamTCP serverSocket(port_);

    serverSocket.listenUsers(maxClientNumber_);
    uint32_t clientID = 1;

    while(runUserActivation_)
    {
        updateClientList();

        if(clientList_.size() < maxClientNumber_)
        {
            //Wait on new users.
            auto client = make_unique<ClientThreadTCP>(move(serverSocket.acceptUsers()),clientUDPManager_);
            client->setID(clientID);
            client->startListen();

            //Assign new client_udp to the vector.
            clientList_.push_back(move(client));
            ++clientID;
        }
    }
}

void Server::updateClientList()
{
    for(auto iter = clientList_.begin(); iter != clientList_.end(); ++iter)
    {
        if(!(*iter)->checkListenEnable())
        {
            clientList_.erase(iter);
        }
    }
}

void Server::stopDataListening()
{
    for(auto iter = clientList_.begin(); iter != clientList_.end(); ++iter)
    {
        (*iter)->stopListen();
        clientList_.erase(iter);
    }
}

