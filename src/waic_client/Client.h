#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include <waic_packet/SendDatagramUDP.h>

#include <cstdint>
#include <string>
#include <memory>

namespace communication
{
    class Client
    {
    public:
        Client(uint16_t portIn, std::string addressIn);
        ~Client();

        void sendData(std::vector<uint8_t> &message);

    private:
        std::unique_ptr<SendDatagramUDP> datagram_;

        uint16_t port_;
        std::string address_;
    };

}
#endif
