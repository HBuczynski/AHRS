#ifndef AHRS_BLACK_BOX_WAICDATAGRAM_H
#define AHRS_BLACK_BOX_WAICDATAGRAM_H

#include "WAICSocket.h"

namespace communication
{
    class WAICDatagram final : public WAICSocket
    {
    public:
        WAICDatagram(SocketUser userIn, uint16_t portIn, std::string address = "NOPE");
        ~WAICDatagram();

        virtual void receivePacket(std::string &message) override;
        virtual void sendPacket(std::string message) override;
    private:

    };
}

#endif