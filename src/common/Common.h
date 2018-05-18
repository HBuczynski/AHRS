#ifndef AHRS_COMMON_H
#define AHRS_COMMON_H

#include <cstdint>
#include <string>

namespace common
{
    struct CommunicationParameters
    {
        uint16_t sourcePortUDP;
        std::string sourceAddressUDP;

        uint16_t destinationPortTCP;
        std::string destinationAddressTCP;
    };

    class Common
    {
    public:
        static CommunicationParameters getCommunicationParameters();
    };
}

#endif //AHRS_COMMON_H
