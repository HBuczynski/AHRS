#include "CommunicationManagerBlackBox.h"

#include <iostream>

using namespace std;
using namespace communication;

CommunicationManagerBlackBox::CommunicationManagerBlackBox(uint16_t serverPort, uint8_t maxUserNumber)
{
    server_ = make_shared<ServerTCP>(serverPort, maxUserNumber);
}

CommunicationManagerBlackBox::~CommunicationManagerBlackBox()
{
}


void CommunicationManagerBlackBox::initialize()
{
    activateServer();
}

void CommunicationManagerBlackBox::activateServer()
{
    server_->startUserActivation();
}




