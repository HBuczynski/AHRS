#include "SendStreamTCP.h"

#include <unistd.h>
#include <memory>

#include <fcntl.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;
using namespace communication;

SendStreamTCP::SendStreamTCP(int sock, struct sockaddr_in sockAddress)
    : sock_(sock),
      sockAddress_(sockAddress)
{

}

SendStreamTCP::SendStreamTCP(uint16_t port, std::string address)
    : port_(port),
      address_(address)
{
    createSocket();
}

SendStreamTCP::~SendStreamTCP()
{
    close(sock_);
}

void SendStreamTCP::createSocket()
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_ == -1)
    {
        throw invalid_argument("Cannot open socket.");

    }

    sockAddress_.sin_family = AF_INET;
    sockAddress_.sin_addr.s_addr = inet_addr(address_.c_str());
    sockAddress_.sin_port = htons(port_);
}

void SendStreamTCP::connectToServer()
{
    if (connect(sock_, (struct sockaddr *) &sockAddress_, sizeof(sockAddress_)) < 0)
    {
        throw invalid_argument("Cannot connect to the communication");
    }
}

vector<uint8_t> SendStreamTCP::receivePacket()
{
    vector<uint8_t > frame(1000);
    fill(frame.begin(), frame.end(), 0);

    if( recv(sock_ , reinterpret_cast<char*>(frame.data()), frame.capacity(), 0) <= 0)
    {
        throw logic_error("Cannot receive packet.");
    }

    return frame;
}

void SendStreamTCP::sendData(vector<uint8_t> message)
{
    if(write( sock_, reinterpret_cast<char*>(message.data()), sizeof(message) ) <= 0)
    {
        throw logic_error("Cannot send packet.");
    }
}