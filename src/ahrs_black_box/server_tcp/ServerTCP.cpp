#include "ServerTCP.h"

#include <protocol/Command.h>
#include <protocol/Response.h>
#include <packet/ListenStreamTCP.h>

#include <algorithm>


#include <iostream>

using namespace std;
using namespace communication;

ServerTCP::ServerTCP(uint16_t port,  uint8_t maxClientNumber, ClientUDPManager* clientUDPManager)
        : port_(port),
          maxClientNumber_(maxClientNumber),
          clientUDPManager_(clientUDPManager),
          runUserActivation_(false)
{ }

ServerTCP::~ServerTCP()
{
    cout << "jestem w destr" << endl;
    stopUserActivation();

}

void ServerTCP::startUserActivation()
{
    runUserActivation_ = true;

    //activationThread_ = thread(&ServerTCP::activateUsers, this);
    activateUsers();
}

void ServerTCP::stopUserActivation()
{
    //runUserActivation_ = false;

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

    while(runUserActivation_)
    {
        updateClientList();

        cout << "w petli " << endl;

        if(clientList_.size() < maxClientNumber_)
        {
            //Wait on new users.
            auto client = make_unique<ClientThreadTCP>(move(serverSocket.acceptUsers()),clientUDPManager_);

            cout << "Aktywowano uzytkownika" << endl;
            client->setID(clientID);
            client->startListen();

            //Assign new client_udp to the vector.
            clientList_.push_back(move(client));
            ++clientID;
        }
    }
}

void ServerTCP::updateClientList()
{
    for(auto iter = clientList_.begin(); iter != clientList_.end(); ++iter)
    {
        if(!(*iter)->checkListenEnable())
        {
            clientList_.erase(iter);
        }
    }
}

void ServerTCP::stopDataListening()
{
    for(auto iter = clientList_.begin(); iter != clientList_.end(); ++iter)
    {
        (*iter)->stopListen();
        clientList_.erase(iter);
    }
}

