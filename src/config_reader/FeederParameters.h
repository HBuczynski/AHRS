#ifndef AHRS_PARAMETERS_H
#define AHRS_PARAMETERS_H

#include <string>

namespace config
{
    const std::string FEEDER_PARAMETERS_FILE_PATH = "/lol";
    const std::string FEEDER_TYPE_FILE_PATH = "/lol";

    enum class FeederMode : uint8_t
    {
        MASTER = 0x05,
        REDUNDANT = 0x10
    };

    struct FeederExternalWireless
    {
        uint16_t firstPort;
        uint16_t secondPort;
        uint8_t maxUserNumber;
    };

    struct FeederInternalWireless
    {
        uint16_t firstPort;
        uint16_t secondPort;
        std::string firstAddress;
        std::string secondAddress;
    };

    struct FeederMessageQueues
    {
        std::string mainProcessQueueName;
        std::string externalCommunicationQueueName;
        std::string internalCommunicationQueueName;
        uint16_t messageQueueNumber;
        uint16_t messageSize;
    };

    struct FeederSharedMemory
    {
        std::string externalMemoryName;
        std::string internalMemoryName;
        uint16_t sharedMemorySize;
    };

    struct FeederType
    {
        FeederMode mode;
        uint8_t processNumber;
    };
}
#endif
