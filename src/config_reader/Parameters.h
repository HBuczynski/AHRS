#ifndef AHRS_PARAMETERS_H
#define AHRS_PARAMETERS_H

namespace config
{
    const std::string filePath = "/lol";

    struct CommunicationParameters
    {
        uint16_t sourcePortUDP;
        std::string sourceAddressUDP;

        uint16_t destinationPortTCP;
        std::string destinationAddressTCP;

        uint8_t maxUserNumber;
    };

    struct CalibratedMagnetometers
    {

    };
}
#endif
