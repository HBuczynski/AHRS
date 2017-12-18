#ifndef AHRS_BLACK_BOX_SEND_DATAGRAM_UDP_H
#define AHRS_BLACK_BOX_SEND_DATAGRAM_UDP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <unistd.h>

#include <cstdint>
#include <vector>
#include <string>

namespace communication
{
    class SendDatagramUDP
    {
    public:
        SendDatagramUDP(uint16_t port, std::string address);
        ~SendDatagramUDP();

        void sendData(std::vector<uint8_t> &message);

    private:
        void createSocket();

        int sock_;

        uint16_t port_;
        std::string address_;
        struct sockaddr_in sockAddress_;
    };
}
#endif
