#ifndef AHRS_PARAMETERS_H
#define AHRS_PARAMETERS_H

#include <string>

namespace config
{
    const std::string FEEDER_PARAMETERS_FILE_PATH = "../../configuration_files/feeder_parameters.json";
    const std::string FEEDER_TYPE_FILE_PATH = "../../configuration_files/feeder_system.json";
    const std::string FEEDER_AIRCRAFTS_DATABASE_FILE_PATH = "../../configuration_files/aircrafts_database.json";
    const std::string FEEDER_AIRCRAFTS_DATABASE_PATH = "../../aircrafts_database/";
    const std::string FEEDER_GPS_DEVICE_FILE = "/dev/ttyS0";

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
        std::string hmQueueName;
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

    struct FeederExecutableFiles
    {
        std::string externalCommunication;
        std::string internalCommunication;
    };
}
#endif
