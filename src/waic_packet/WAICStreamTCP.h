#ifndef AHRS_BLACK_BOX_WAICSTREAM_H
#define AHRS_BLACK_BOX_WAICSTREAM_H

#include "WAICSocket.h"
#include <memory>

namespace communication
{
    class WAICStreamTCP final : public WAICSocket
    {
    public:
        WAICStreamTCP();
        WAICStreamTCP(SocketUser userIn, uint16_t portIn = 0, std::string address = "NOPE");
        ~WAICStreamTCP();

        virtual void receivePacket(std::string &message) override;
        virtual void sendPacket(std::string message) override;

        void listenUsers(uint32_t userNumber);
        void acceptUsers(std::shared_ptr<WAICStreamTCP> socket);
        void connectToServer();

    };
}

#endif
