#include "CommandHandlerVisitor.h"
#include <protocol/DataResponse.h>

#include <ahrs_black_box/server_tcp/ClientThreadTCP.h>

#include <iostream>

using namespace std;
using namespace communication;

CommandHandlerVisitor::CommandHandlerVisitor()
{}

CommandHandlerVisitor::~CommandHandlerVisitor()
{}

void CommandHandlerVisitor::visit(InitConnectionCommand &command)
{
    auto newClient = make_shared<ClientUDP>(command.getPort(), command.getAddress());

    cout << command.getAddress() << endl;
    cout << command.getPort() << endl;
    cout << currentClient_->getID() << endl;

    clientUDPManager_->getClientList();

    clientUDPManager_->insertNewClient(make_pair((newClient), currentClient_->getID()));
    response_ = make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(EndConnectionCommand &command)
{
    clientUDPManager_->removeClient(currentClient_->getID());
    response_ = make_unique<DataResponse>("OK");
}

unique_ptr<Response> CommandHandlerVisitor::getResponse()
{
    return move(response_);
}

void CommandHandlerVisitor::initializeClientUDPManager(ClientUDPManager* clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
}

void CommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}

void CommandHandlerVisitor::visit(CallibrateMagnetometerCommand &command)
{

}

void CommandHandlerVisitor::visit(CollectDataCommand &command)
{

}

void CommandHandlerVisitor::visit(SetPlaneMagnetometerCommand &command)
{

}
