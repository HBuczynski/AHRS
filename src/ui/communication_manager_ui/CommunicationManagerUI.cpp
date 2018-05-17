#include "CommunicationManagerUI.h"

#include <interfaces/wireless_commands/InitConnectionCommand.h>
#include <interfaces/wireless_commands/CollectDataCommand.h>
#include <interfaces/wireless_commands/EndConnectionCommand.h>
#include <iostream>

#include <thread>
#include <chrono>

using namespace std;
using namespace communication;

CommunicationManagerUI::CommunicationManagerUI(CommunicationParameters parameters)
    :   parameters_(parameters)
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
    client_->startCommandSending();
}

void CommunicationManagerUI::sendCommands()
{
    auto command = make_unique<InitConnectionCommand>(parameters_.sourcePortUDP, parameters_.sourceAddressUDP);
    auto command2 = make_unique<CollectDataCommand>();
    auto command3 = make_unique<EndConnectionCommand>();

    client_->sendCommand(move(command));
    std::this_thread::sleep_for(1s);
    client_->sendCommand(move(command2));
    std::this_thread::sleep_for(1s);
    client_->sendCommand(move(command3));
}



