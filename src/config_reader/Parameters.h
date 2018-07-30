#ifndef AHRS_PARAMETERS_H
#define AHRS_PARAMETERS_H

namespace config
{
    const std::string filePath = "/lol";

    struct FeederParameters
    {
        uint16_t sourcePort;
        uint8_t maxUserNumber;

        std::string mainProcessQueueName;
        std::string externalCommunicationQueueName;
        std::string internalCommunicationQueueName;
        uint16_t messageSize;

        std::string externalMemoryName;
        std::string internalMemoryName;
        uint16_t sharedMemorySize;
    };

    struct UIParameters
    {
        uint16_t sourcePort;
        std::string sourceAddress;
        uint16_t destinationPort;
        std::string destinationAddress;

        std::string mainProcessQueueName;
        std::string mainCommunicationQueueName;
        std::string redundantCommunicationQueueName;
        std::string guiProcessQueueName;
        uint16_t messageSize;

        std::string dataSharedMemory;
        uint16_t sharedMemorySize;
    };
}
#endif
