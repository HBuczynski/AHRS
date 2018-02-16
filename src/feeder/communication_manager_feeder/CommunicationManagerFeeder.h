#ifndef AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H
#define AHRS_BLACK_BOX_COMMUNICATION_MANAGER_H

#include <server_tcp/ServerTCP.h>
#include <client_udp/ClientUDP.h>

#include <memory>
#include <list>
#include <utility>
#include <mutex>

namespace communication
{
    class CommunicationManagerFeeder
    {
    public:
        CommunicationManagerFeeder(uint16_t serverPort, uint8_t maxUserNumber);
        ~CommunicationManagerFeeder();

        void initialize();

    private:
        void activateServer();

        std::shared_ptr<ServerTCP> server_;
    };
}
#endif