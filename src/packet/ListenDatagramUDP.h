#ifndef AHRS_BLACK_BOX_WAICDATAGRAM_H
#define AHRS_BLACK_BOX_WAICDATAGRAM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string>
#include <vector>
#include <memory>

#include "SendDatagramUDP.h"

namespace communication
{
    class ListenDatagramUDP
    {
    public:
        ListenDatagramUDP(uint16_t port);
        ~ListenDatagramUDP();

        std::vector<uint8_t > receivePacket();

    private:
        void createSocket();

        void checksum(const std::vector<uint8_t> msg);

        int sock_;
        struct sockaddr_in sockAddress_;

        uint16_t port_;
        std::string address_;

    };
}

#endif