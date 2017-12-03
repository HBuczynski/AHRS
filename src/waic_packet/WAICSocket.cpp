#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include <stdexcept>

#include "WAICSocket.h"

using namespace std;
using namespace communication;

WAICSocket::WAICSocket()
{
}

WAICSocket::WAICSocket(SocketUser userIn, uint16_t portIn, string addressIn)
    : user(userIn),
      port(portIn),
      address(addressIn)
{
    if(user == SERVER)
    {
        createSocketWithBinding();
    }
    else
    {
        createSocketWithoutBinding();
    }
}

WAICSocket::~WAICSocket()
{
}

void WAICSocket::createSocketWithBinding()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock == -1)
    {
        throw invalid_argument("Cannot open socket.");

    }

    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons(port);

    if (bind(sock,(struct sockaddr *)&sockAddress, sizeof sockAddress) == -1)
    {
        throw logic_error("Cannot bind datagram socket.");
    }
}

void WAICSocket::createSocketWithoutBinding()
{
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        throw invalid_argument("Could not create socket");
    }

    struct hostent *hp = gethostbyname(address.c_str());

    if (hp == (struct hostent *) 0)
    {
        throw invalid_argument("Unknown host.");
    }

    memcpy((char *) &sockAddress.sin_addr, (char *) hp->h_addr, hp->h_length);

    sockAddress.sin_family = AF_INET;
    sockAddress.sin_port = htons(port);
}

string WAICSocket::getAddress()
{
    return string(inet_ntoa(sockAddress.sin_addr));
}

uint16_t WAICSocket::getPort()
{
    return port;
}


