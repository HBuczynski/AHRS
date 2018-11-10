#ifndef AHRS_BLACK_BOX_SENDSTREAMTCP_H
#define AHRS_BLACK_BOX_SENDSTREAMTCP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string>
#include <vector>

namespace communication
{
    class SendStreamTCP
    {
    public:
        SendStreamTCP(int sock, struct sockaddr_in sockAddress);
        SendStreamTCP(uint16_t port, std::string address);
        ~SendStreamTCP();

        std::vector<uint8_t > receivePacket();
        void sendData(std::vector<uint8_t> message);

        void connectToServer();
        void setTimeout();

    private:
        void createSocket();
        void checksum(const std::vector<uint8_t> msg);

        int sock_;
        struct sockaddr_in sockAddress_;

        uint16_t port_;
        std::string address_;

        uint8_t TIMEOUT_IN_SECONDS = 3;
    };
}
#endif //AHRS_BLACK_BOX_SENDSTREAMTCP_H
