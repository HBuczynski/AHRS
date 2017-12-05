#include "WAICDatagramUDP.h"

#include <stdexcept>
#include <iostream>
using namespace std;
using namespace communication;

WAICDatagramUDP::WAICDatagramUDP(SocketUser userIn, uint16_t portIn, string address)
        : WAICSocket(userIn, SOCK_DGRAM, portIn, address)
{

}

WAICDatagramUDP::~WAICDatagramUDP()
{

}

void WAICDatagramUDP::receivePacket(std::string &message)
{
    char buffer[1024];
    socklen_t slen = sizeof(sockAddress);

    if ( recvfrom(sock, buffer, 1024, 0, (struct sockaddr *) &sockAddress, &slen) == -1 )
    {
        throw logic_error("Cannot receive packet.");
    }

    message = string(buffer);
}

void WAICDatagramUDP::sendPacket(std::string message)
{
    if ( sendto(sock, message.c_str(), sizeof(message) ,0, (struct sockaddr *) &sockAddress, sizeof(sockAddress)) == -1 )
    {
        cout << "zle" << endl;
        throw logic_error("Cannot send packet.");

    }
}
