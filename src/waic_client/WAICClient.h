#ifndef AHRS_BLACK_BOX_WAIC_CLIENT_H
#define AHRS_BLACK_BOX_WAIC_CLIENT_H

#include <waic_packet/WAICDatagramUDP.h>

#include <cstdint>
#include <string>
#include <memory>

namespace communication
{
    class WAICClient
    {
    public:
        WAICClient(uint16_t portIn, std::string addressIn);
        ~WAICClient();

        void sendData(std::string message);

    private:
        std::shared_ptr<WAICDatagramUDP> datagram;

        uint16_t port_;
        std::string address_;
    };

}
#endif
