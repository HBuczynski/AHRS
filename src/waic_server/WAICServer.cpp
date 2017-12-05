#include "WAICServer.h"
#include <waic_protocol/WAICCommand.h>
#include <waic_protocol/WAICResponse.h>

#include <algorithm>

using namespace std;
using namespace communication;

WAICServer::WAICServer(uint16_t portIn,  uint8_t maxClientNumberIn)
        : port(portIn),
          maxClientNumber(maxClientNumberIn),
          runUserActivation(false),
          clientsNumber(0)
{
}

WAICServer::~WAICServer()
{
    for_each(clientList.begin(), clientList.end(), [](shared_ptr<ClientThread>  clientThr)
    {
        if(clientThr->clientThread.joinable())
        {
            clientThr->clientThread.join();
        }
    });

    if(activationThread.joinable())
    {
        activationThread.join();
    }
}

void WAICServer::startUserActivation()
{
    runUserActivation = true;

    activationThread = thread(&WAICServer::activateUsers, this);
}

void WAICServer::stopUserActivation()
{
    runUserActivation = false;
}

void WAICServer::activateUsers()
{
    WAICStreamTCP serverSocket(SERVER, port);

    serverSocket.listenUsers(maxClientNumber);

    while(runUserActivation)
    {
        if(clientsNumber < 2)
        {
            //Wait on new users.
            shared_ptr<ClientThread> client = make_shared<ClientThread>();
            client->streamTCP = make_shared<WAICStreamTCP>();
            serverSocket.acceptUsers(client->streamTCP);

            client->clientThread = thread(&WAICServer::listenData, this, client);

            //Assign new client to the vector.
            clientList.push_back(client);
            ++clientsNumber;
        }
    }
}

void WAICServer::listenData(shared_ptr<ClientThread> client)
{
    string packet;
    bool runThread = true;
    // TODO: sprawdzenie zerwania połączenia tworzenie klienta do wysyłania pod UPD

    while(runThread)
    {
        client->streamTCP->receivePacket(packet);
        vector<uint8_t > bytesFrame(packet.begin(), packet.end());

        WAICCommandType commandType = static_cast<WAICCommandType >(bytesFrame[5]);

        auto commandHandler = supportedCommands.find(commandType);

        if(commandHandler != supportedCommands.end())
        {
           shared_ptr<WAICResponse> response = commandHandler->second->handler(bytesFrame, client->id);

           client->streamTCP->sendPacket(string(response->getFrameBytes().begin(), response->getFrameBytes().end()));
        }

        if(commandType == END_CONNECTION)
        {
            runThread = false;
            removeClient(client);
        }
    }

    --clientsNumber;
}

void WAICServer::registerCommand(WAICCommandType type, shared_ptr<WAICCommandHandler> handler)
{
    supportedCommands[type] = handler;
}

void WAICServer::unregisterCommand(WAICCommandType type)
{
    supportedCommands.erase(type);
}

void WAICServer::removeClient(shared_ptr<ClientThread> client)
{
    for(auto iter = clientList.begin(); iter != clientList.end(); ++iter)
    {
        if((*iter)->id == client->id)
        {
            clientList.erase(iter);
        }
    }
}
