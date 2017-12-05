#ifndef AHRS_BLACK_BOX_WAICDATAGRAM_H
#define AHRS_BLACK_BOX_WAICDATAGRAM_H

#include "WAICSocket.h"

namespace communication
{
    class WAICDatagramUDP final : public WAICSocket
    {
    public:
        WAICDatagramUDP(SocketUser userIn, uint16_t portIn = 0, std::string address = "NOPE");
        virtual ~WAICDatagramUDP();

        virtual void receivePacket(std::string &message) override;
        virtual void sendPacket(std::string message) override;
    private:

    };
}

#endif