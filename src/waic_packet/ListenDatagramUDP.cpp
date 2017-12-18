#include "ListenDatagramUDP.h"

#include <stdexcept>

using namespace std;
using namespace communication;

ListenDatagramUDP::ListenDatagramUDP(uint16_t port)
        : port_(port)
{
    createSocket();
}

void ListenDatagramUDP::createSocket()
{
    sock_ = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_ == -1)
    {
        throw invalid_argument("Cannot open socket.");

    }

    sockAddress_.sin_family = AF_INET;
    sockAddress_.sin_addr.s_addr = INADDR_ANY;
    sockAddress_.sin_port = htons(port_);

    if (bind(sock_,(struct sockaddr *)&sockAddress_, sizeof sockAddress_) == -1)
    {
        throw logic_error("Cannot bind datagram socket.");
    }
}

ListenDatagramUDP::~ListenDatagramUDP()
{
    close(sock_);
}


vector<uint8_t> ListenDatagramUDP::receivePacket()
{
    vector<uint8_t > frame(1000);
    fill(frame.begin(), frame.end(), 0);

    socklen_t slen = sizeof(sockAddress_);

    if ( recvfrom(sock_, reinterpret_cast<char*>(frame.data()), frame.capacity(), 0, (struct sockaddr *) &sockAddress_, &slen) == -1 )
    {
        throw logic_error("Cannot receive packet.");
    }

    return frame;
}


