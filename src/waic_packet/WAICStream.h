#ifndef AHRS_BLACK_BOX_WAICSTREAM_H
#define AHRS_BLACK_BOX_WAICSTREAM_H

#include "WAICSocket.h"

namespace communication
{
    class WAICStream final : public WAICSocket
    {
    public:

        WAICStream(SocketUser userIn, uint16_t portIn, std::string address = "NOPE");
        ~WAICStream();

        virtual void receivePacket(std::string &message) override;
        virtual void sendPacket(std::string message) override;

        void listenUsers(uint32_t userNumber);
        int acceptUsers(WAICStream &socket);
        void connectToServer();

    };
}

#endif
