#include "CommunicationManagerUI.h"

#include <protocol/InitConnectionCommand.h>
#include <protocol/CollectDataCommand.h>
#include <protocol/EndConnectionCommand.h>
#include <iostream>

using namespace std;
using namespace communication;

CommunicationManagerUI::CommunicationManagerUI(CommunicationParameters parameters)
    :   ResponseNotification(),
        parameters_(parameters)
{
    server_ = make_unique<ServerUDP>(parameters_.sourcePortUDP);
    client_ = make_unique<ClientTCP>(parameters_.destinationPortTCP, parameters_.destinationAddressTCP);
}

CommunicationManagerUI::~CommunicationManagerUI()
{
}

void CommunicationManagerUI::initializeServer()
{
    server_->startListening();
}

void CommunicationManagerUI::initializeClientConnection()
{
    client_->connectToServer();
    // to do: exception
    client_->startCommandSending();
}

void CommunicationManagerUI::sendCommands()
{
    auto command = make_unique<InitConnectionCommand>(parameters_.sourcePortUDP, parameters_.sourceAddressUDP);
    auto command2 = make_unique<CollectDataCommand>();
    auto command3 = make_unique<EndConnectionCommand>();

    client_->sendCommand(move(command), this);
    client_->sendCommand(move(command2), this);
    client_->sendCommand(move(command3), this);
}

void CommunicationManagerUI::received(std::vector<uint8_t> responseFrame)
{

}



