#ifndef AHRS_BLACK_BOX_WAICSOCKET_H
#define AHRS_BLACK_BOX_WAICSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <unistd.h>

#include <string>

namespace communication
{
    enum SocketUser
    {
        SERVER,
        CLIENT
    };

    class WAICSocket
    {
    public:
        WAICSocket();
        WAICSocket(SocketUser userIn, uint16_t portIn, std::string address = "NOPE");
        virtual ~WAICSocket();

        virtual void receivePacket(std::string &message) = 0;
        virtual void sendPacket(std::string message) = 0;

        std::string getAddress();
        uint16_t getPort();

    protected:
        int sock;
        uint16_t port;
        std::string address;
        struct sockaddr_in sockAddress;

        SocketUser user;

    private:
        void createSocketWithBinding();
        void createSocketWithoutBinding();
    };
}
#endif
