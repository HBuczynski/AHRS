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

    parameters_ = ConfigurationReader::getUIParameters(config::filePath);

    server_ = make_unique<ServerUDP>(parameters_.sourcePort);
    client_ = make_unique<ClientTCP>(parameters_.destinationPort, parameters_.destinationAddress);

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

    auto command = make_unique<InitConnectionCommand>(parameters_.sourcePort, parameters_.sourceAddress);
    sendCommands(move(command));
}

void CommunicationManagerUI::sendCommands(unique_ptr<Command> command)
{
    client_->sendCommand(move(command));
}



