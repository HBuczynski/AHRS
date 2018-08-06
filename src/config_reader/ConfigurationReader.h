#ifndef AHRS_CONFIGURATIONREADER_H
#define AHRS_CONFIGURATIONREADER_H

#include "JSONParser.h"
#include "FeederParameters.h"
#include "UIParameters.h"

#include <memory>

namespace config
{
    class ConfigurationReader
    {
    public:
        ConfigurationReader();
        ~ConfigurationReader();


        static UIWirelessCommunication getUIWirelessCommunication(const std::string &filePath);
        static UIMessageQueues getUIMessageQueues(const std::string &filePath);
        static UISharedMemory getUISharedMemory(const std::string &filePath);

        static void setUICommunicationMode(const std::string &filePath, uint8_t processNumber, UICommunicationMode mode);

        static FeederExternalWireless getFeederExternalWireless(const std::string &filePath);
        static FeederInternalWireless getFeederInternalWireless(const std::string &filePath);
        static FeederMessageQueues getFeederMessageQueues(const std::string &filePath);
        static FeederSharedMemory getFeederSharedMemory(const std::string &filePath);
        static FeederType getFeederType(const std::string &filePath);

        static void setFeederSystemValue(const std::string &filePath, FeederMode mode);
    };
}

#endif