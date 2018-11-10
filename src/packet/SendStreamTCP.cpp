#include "SendStreamTCP.h"

#include <unistd.h>
#include <memory>

#include <fcntl.h>
#include <iostream>
#include <arpa/inet.h>
#include <utility/BytesConverter.h>
#include <checksum/Checksum.h>

using namespace std;
using namespace utility;
using namespace communication;

SendStreamTCP::SendStreamTCP(int sock, struct sockaddr_in sockAddress)
    : sock_(sock),
      sockAddress_(sockAddress)
{
//    tv.tv_sec = 10; /* seconds */
//    tv.tv_usec = 0;
//
//    if(setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
//        printf("Cannot Set SO_SNDTIMEO for socket\n");
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

    const auto receivedBytesNumber = recv(sock_ , reinterpret_cast<char*>(frame.data()), frame.capacity(), 0);

    if( receivedBytesNumber <= 0)
    {
        throw logic_error("Cannot receive packet.");
    }

    frame.resize(receivedBytesNumber);
    frame.shrink_to_fit();

    checksum(frame);

    return frame;
}

void SendStreamTCP::checksum(const std::vector<uint8_t> msg)
{
    const auto crcFromFrame = BytesConverter::fromVectorOfUINT8toUINT32(msg, msg.size() - sizeof(uint32_t));
    const auto parityFromFrame = msg[msg.size() - sizeof(uint32_t) - sizeof(uint8_t)];

    const auto commandFrame = vector<uint8_t>(msg.begin(), msg.begin() + msg.size() - sizeof(uint8_t) - sizeof(uint32_t));
    const auto parityBit = Checksum::parityBit(commandFrame);
    const auto crc32 = Checksum::crc32(commandFrame);

    if(crcFromFrame != crc32 || parityFromFrame != parityBit)
    {
        throw logic_error("Checksum is incorrect.");
    }
}

void SendStreamTCP::sendData(vector<uint8_t> message)
{
    auto parityBit = Checksum::parityBit(message);
    const auto crc32 = Checksum::crc32(message);

    message.push_back(parityBit);
    BytesConverter::appendUINT32toVectorOfUINT8(crc32, message);

    if(write( sock_, reinterpret_cast<char*>(message.data()), sizeof(uint8_t)*message.size() ) <= 0)
    {
        throw logic_error("Cannot send packet.");
    }
}

