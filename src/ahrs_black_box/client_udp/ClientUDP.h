#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include <packet/SendDatagramUDP.h>

#include <cstdint>
#include <string>
#include <memory>

namespace communication
{
    class ClientUDP
    {
    public:
        ClientUDP(uint16_t portIn, std::string addressIn);
        ~ClientUDP();

        void sendData(std::vector<uint8_t> &message);

    private:
        std::unique_ptr<SendDatagramUDP> datagram_;

        uint16_t port_;
        std::string address_;
    };

}
#endif
