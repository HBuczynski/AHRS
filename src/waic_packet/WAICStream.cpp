#include "WAICStream.h"

#include <stdexcept>

using namespace std;
using namespace communication;

WAICStream::WAICStream(SocketUser userIn, uint16_t portIn, string address)
        : WAICSocket(userIn, portIn, address)
{

}

WAICStream::~WAICStream()
{

}

void WAICStream::listenUsers(uint32_t userNumber)
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

int WAICStream::acceptUsers(WAICStream &socket)
{
    int clientSock;

    if(user == SERVER)
    {
        int structSize = sizeof(struct sockaddr_in);
        clientSock = accept(sock, (struct sockaddr *) &socket.sockAddress, (socklen_t *) &structSize);
    }
    else
    {
        throw logic_error("User cannot accept users.");
    }

    return clientSock;
}

void WAICStream::connectToServer()
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

void WAICStream::receivePacket(std::string &message)
{
    char buffer[1024]; // to do

    if( recv(sock , buffer , 1024 , 0) < 0)
    {
        throw logic_error("Cannot receive packet.");
    }

    message = string(buffer);
}

void WAICStream::sendPacket(std::string message)
{
    if(write( sock, message.c_str(), sizeof(message) ) == -1)
    {
        throw logic_error("Cannot send packet.");
    }
}
