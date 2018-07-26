#include "CommunicationManagerUI.h"

#include <interfaces/wireless_commands/InitConnectionCommand.h>
#include <interfaces/wireless_commands/CollectDataCommand.h>
#include <interfaces/wireless_commands/EndConnectionCommand.h>
#include <iostream>

#include <thread>
#include <chrono>

using namespace std;
using namespace config;
using namespace communication;

CommunicationManagerUI::CommunicationManagerUI()
{

    parameters_ = ConfigurationReader::getCommunicationParameters(config::filePath);

    server_ = make_unique<ServerUDP>(parameters_.sourcePortUDP);
    client_ = make_unique<ClientTCP>(parameters_.destinationPortTCP, parameters_.destinationAddressTCP);

    initializeServer();
    initializeClientConnection();
}

CommunicationManagerUI::~CommunicationManagerUI()
{}

void CommunicationManagerUI::initializeServer()
{
    server_->startListening();
}

void CommunicationManagerUI::initializeClientConnection()
{
    client_->connectToServer();
    client_->startCommandSending();

    auto command = make_unique<InitConnectionCommand>(parameters_.sourcePortUDP, parameters_.sourceAddressUDP);
    sendCommands(move(command));
}

void CommunicationManagerUI::sendCommands(unique_ptr<Command> command)
{
    client_->sendCommand(move(command));
}



