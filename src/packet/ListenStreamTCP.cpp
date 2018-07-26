#include "ListenStreamTCP.h"

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;
using namespace communication;


ListenStreamTCP::ListenStreamTCP(uint16_t port)
    : port_(port)
{
    createSocket();
}

ListenStreamTCP::~ListenStreamTCP()
{
    close(sock_);
}

void ListenStreamTCP::createSocket()
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_ == -1)
    {
        throw invalid_argument("Cannot open socket.");

    }

    sockAddress_.sin_family = AF_INET;
    sockAddress_.sin_addr.s_addr = INADDR_ANY;
    sockAddress_.sin_port = htons(port_);

    int yes =1;
    if (setsockopt(sock_,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
    {
        throw logic_error("Cannot set socket options.");
    }

    if (bind(sock_,(struct sockaddr *)&sockAddress_, sizeof sockAddress_) == -1)
    {
        throw logic_error("Cannot bind stream socket.");
    }
}

void ListenStreamTCP::listenUsers(uint32_t userNumber)
{
    listen(sock_, userNumber);
}

unique_ptr<SendStreamTCP> ListenStreamTCP::acceptUsers()
{
    int clientSock;
    struct sockaddr_in sockAddress;

    int structSize = sizeof(struct sockaddr_in);
    clientSock = accept(sock_, (struct sockaddr *) &sockAddress, (socklen_t *) &structSize);

    unique_ptr<SendStreamTCP> newUser(new SendStreamTCP(clientSock, sockAddress));

    return newUser;
}

string ListenStreamTCP::getAddress()
{

    string address(inet_ntoa(sockAddress_.sin_addr));

    return address;
}