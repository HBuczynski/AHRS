#include "CommandHandlerVisitor.h"

#include <protocol/DataResponse.h>
#include <protocol/ImuData.h>

#include <feeder/server_tcp/ClientThreadTCP.h>

#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

CommandHandlerVisitor::CommandHandlerVisitor()
    : logger_(Logger::getInstance())
{}

CommandHandlerVisitor::~CommandHandlerVisitor()
{}

void CommandHandlerVisitor::visit(InitConnectionCommand &command)
{
    auto newClient = make_shared<ClientUDP>(command.getPort(), command.getAddress());

    if(logger_.isInformationEnable())
    {
        const string message = string("CommandHandler :: Received InitConnectionCommand from ClientID -") +
                         to_string(currentClient_->getID())
                         + string("-. Command data: port-") + to_string(command.getPort()) + string("; address-") +
                         command.getAddress();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    clientUDPManager_->insertNewClient(make_pair((newClient), currentClient_->getID()));
    response_ = make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(EndConnectionCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("CommandHandler :: Received EndConnectionCommand from ClientID -") +
                         to_string(currentClient_->getID())
                         + string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    clientUDPManager_->removeClient(currentClient_->getID());
    currentClient_->stopListen();

    response_ = make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(CallibrateMagnetometerCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("CommandHandler :: Received CallibrateMagnetometerCommand from ClientID -") +
                         to_string(currentClient_->getID())
                         + string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CommandHandlerVisitor::visit(CollectDataCommand &command)
{
    ImuData imuData(12);
    clientUDPManager_->broadcast(imuData.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("CommandHandler :: Received CollectDataCommand from ClientID -") +
                         to_string(currentClient_->getID())
                         + string("-.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    response_ = make_unique<DataResponse>("OK");
}

void CommandHandlerVisitor::visit(SetPlaneMagnetometerCommand &command)
{

}

unique_ptr<Response> CommandHandlerVisitor::getResponse()
{
    return move(response_);
}

void CommandHandlerVisitor::initializeClientUDPManager(shared_ptr<ClientUDPManager> clientUDPManager)
{
    clientUDPManager_ = clientUDPManager;
}

void CommandHandlerVisitor::initializeCurrentClient(ClientThreadTCP *client)
{
    currentClient_ = client;
}
