#include "WAICCommunicationManager.h"

#include "WAICInitConnectionHandler.h"
#include "WAICEndConnectionHandler.h"


#include <iostream>

using namespace std;
using namespace communication;

WAICCommunicationManager::WAICCommunicationManager(uint16_t serverPort, uint8_t maxUserNumber)
{
    server_ = make_shared<WAICServer>(serverPort, maxUserNumber);

    initialize();
}

WAICCommunicationManager::~WAICCommunicationManager()
{
}

void WAICCommunicationManager::initialize()
{
    registerHandlers();
    activateServer();
}

void WAICCommunicationManager::registerHandlers()
{
    function<const list<pair<shared_ptr<WAICClient>, uint8_t>> & ()> getClientListCallback = bind(&WAICCommunicationManager::getClientList, this);
    function<void (pair<shared_ptr<WAICClient>, uint8_t>) > insertNewClientCallback = bind(&WAICCommunicationManager::insertNewClient, this, std::placeholders::_1);
    function<void (uint8_t) > removeClientCallback = bind(&WAICCommunicationManager::removeClient, this, std::placeholders::_1);

    shared_ptr<WAICCommandHandler> initConnectionHandler(new WAICInitConnectionHandler(insertNewClientCallback));
    shared_ptr<WAICCommandHandler> endConnectionHandler(new WAICEndConnectionHandler(removeClientCallback));

    server_->registerCommand(INIT_CONNECTION, initConnectionHandler);
    server_->registerCommand(END_CONNECTION, endConnectionHandler);
}

void WAICCommunicationManager::activateServer()
{
    server_->startUserActivation();
}

const list<pair<shared_ptr<WAICClient>, uint8_t>> & WAICCommunicationManager::getClientList()
{
    lock_guard<mutex> lock(listMutex);
    return clientList;
}

void WAICCommunicationManager::insertNewClient(pair<shared_ptr<WAICClient>, uint8_t> newClient)
{
    lock_guard<mutex> lock(listMutex);
    clientList.push_back(newClient);
}

void WAICCommunicationManager::removeClient(uint8_t id)
{
    lock_guard<mutex> lock(listMutex);

    for(auto iter = clientList.begin(); iter != clientList.end(); ++iter)
    {
        if((*iter).second == id)
        {
            clientList.erase(iter);
        }
    }
}

