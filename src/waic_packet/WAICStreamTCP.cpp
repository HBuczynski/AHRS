#include "WAICStreamTCP.h"

#include <stdexcept>

using namespace std;
using namespace communication;

WAICStreamTCP::WAICStreamTCP()
{

}

WAICStreamTCP::WAICStreamTCP(SocketUser userIn, uint16_t portIn, string address)
        : WAICSocket(userIn, SOCK_STREAM, portIn, address)
{

}

WAICStreamTCP::~WAICStreamTCP()
{

}

void WAICStreamTCP::listenUsers(uint32_t userNumber)
{
    if(user == SERVER)
    {
        listen(sock, userNumber);
    }
    else
    {
        throw logic_error("User cannot use listen method.");
    }
}

void WAICStreamTCP::acceptUsers(std::shared_ptr<WAICStreamTCP> socket)
{
    int clientSock;

    if(user == SERVER)
    {
        int structSize = sizeof(struct sockaddr_in);
        clientSock = accept(sock, (struct sockaddr *) &socket->sockAddress, (socklen_t *) &structSize);
    }
    else
    {
        throw logic_error("User cannot accept users.");
    }
}

void WAICStreamTCP::connectToServer()
{
    if(user == CLIENT)
    {
        if (connect(sock, (struct sockaddr *) &sockAddress, sizeof(sockAddress)) < 0)
        {
            throw invalid_argument("Cannot connect to the server");
        }
    }
    else
    {
        throw logic_error("Server cannot use connect method.");
    }
}

void WAICStreamTCP::receivePacket(std::string &message)
{
    char buffer[1024]; // to do

    if( recv(sock , buffer , 1024 , 0) < 0)
    {
        throw logic_error("Cannot receive packet.");
    }

    message = string(buffer);
}

void WAICStreamTCP::sendPacket(std::string message)
{
    if(write( sock, message.c_str(), sizeof(message) ) == -1)
    {
        throw logic_error("Cannot send packet.");
    }
}
