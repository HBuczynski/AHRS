#include "CommunicationManagerUI.h"

#include <protocol/InitConnectionCommand.h>
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

    client_->sendCommand(move(command), this);
}

void CommunicationManagerUI::received(std::vector<uint8_t> responseFrame)
{
    cout << "Otrzymano odpowiedź " << endl;
}



