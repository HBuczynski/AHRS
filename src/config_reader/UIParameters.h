#ifndef AHRS_UI_PARAMETERS_H
#define AHRS_UI_PARAMETERS_H

#include <string>

namespace config
{
    const std::string UI_PARAMETERS_FILE_PATH = "../../configuration_files/ui_parameters.json";
    const std::string UI_COMMUNICATION_PROCESS_PARAMETERS_PATH = "../../configuration_files/ui_communication_processes.json";
    const std::string UI_BUTTONS_PARAMETERS_PATH = "../../configuration_files/ui_buttons.json";


    enum UICommunicationMode : uint8_t
    {
        MASTER = 0x05,
        REDUNDANT = 0x0A
    };

    struct UICommunicationProcess
    {
        UICommunicationMode mode;
        uint8_t processNumber;
    };

    struct UIWirelessCommunication
    {
        uint16_t firstSourcePort;
        std::string firstSourceAddress;
        uint16_t firstDestinationPort;
        std::string firstDestinationAddress;

        uint16_t secondSourcePort;
        std::string secondSourceAddress;
        uint16_t secondDestinationPort;
        std::string secondDestinationAddress;
    };

    struct UIMessageQueues
    {
        std::string mainProcessQueueName;
        std::string firstCommunicationQueueName;
        std::string secondCommunicationQueueName;
        std::string guiProcessQueueName;
        std::string hmQueueName;

        uint16_t messageQueueNumber;
        uint16_t messageSize;
    };

    struct UISharedMemory
    {
        std::string sharedMemoryName;
        uint16_t sharedMemorySize;
    };

    struct UICommunicationSystemParameters
    {
        UICommunicationProcess firstProcess;
        UICommunicationProcess secondProcess;
    };

    struct UIExecutableFiles
    {
        std::string externalCommunicationProcess;
        std::string guiProcess;
    };
}

#endif
