#include "CommunicationManagerFeeder.h"

#include <iostream>

using namespace std;
using namespace communication;

CommunicationManagerFeeder::CommunicationManagerFeeder(uint16_t serverPort, uint8_t maxUserNumber)
{
    server_ = make_shared<ServerTCP>(serverPort, maxUserNumber);
}

CommunicationManagerFeeder::~CommunicationManagerFeeder()
{
}


void CommunicationManagerFeeder::initialize()
{
    activateServer();
}

void CommunicationManagerFeeder::activateServer()
{
    server_->startUserActivation();
}




