#include "Server.h"

#include <waic_protocol/Command.h>
#include <waic_protocol/Response.h>
#include <waic_packet/ListenStreamTCP.h>

#include <algorithm>

using namespace std;
using namespace communication;

Server::Server(uint16_t port,  uint8_t maxClientNumber)
        : port_(port),
          maxClientNumber_(maxClientNumber),
          runUserActivation_(false)
{
}

Server::~Server()
{
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

void Server::initializeHandlers(CallbackFunctions callbackFunctions)
{
    callbackFunctions_ = callbackFunctions;
}

void Server::activateUsers()
{
    ListenStreamTCP serverSocket(port_);

    serverSocket.listenUsers(maxClientNumber_);
    uint32_t clientID = 1;

    while(runUserActivation_)
    {
        updateClientList();

        if(clientList_.size() < 2)
        {
            //Wait on new users.
            unique_ptr<ClientThreadTCP> client = make_unique<ClientThreadTCP>(move(serverSocket.acceptUsers()),callbackFunctions_);
            client->setID(clientID);
            client->startListen();

            //Assign new client to the vector.
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

