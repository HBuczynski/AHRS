#ifndef AHRS_UI_PARAMETERS_H
#define AHRS_UI_PARAMETERS_H

namespace config
{
    const std::string uiFilePath = "/lol";

    enum class UICommunicationMode : uint8_t
    {
        MASTER = 0x05,
        REDUNDANT = 0x10
    };

    struct UIWirelessCommunication
    {
        uint16_t sourcePort;
        std::string sourceAddress;
        uint16_t destinationPort;
        std::string destinationAddress;
    };

    struct UIMessageQueues
    {
        std::string mainProcessQueueName;
        std::string firstProcQueueName;
        std::string secondProcQueueName;
        std::string guiProcessQueueName;
        uint16_t messageSize;
    };

    struct UISharedMemory
    {
        std::string dataSharedMemory;
        uint16_t sharedMemorySize;
    };

    struct UICommunicationProcess
    {
        UICommunicationMode mode;
        uint8_t processNumber;
    };
}

#endif //AHRS_UI_PARAMETERS_H
