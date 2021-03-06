#ifndef AHRS_CONFIGURATIONREADER_H
#define AHRS_CONFIGURATIONREADER_H

#include "JSONParser.h"
#include "FeederParameters.h"
#include "UIParameters.h"


#include <hal/include/GPIOInterface.h>
#include <memory>
#include <vector>

namespace config
{
    class ConfigurationReader
    {
    public:
        ConfigurationReader();
        ~ConfigurationReader();

        /**** UI Cockpit commands ****/
        // Getters
        static UIExecutableFiles getUIExecutableFiles(const std::string &filePath);
        static UIWirelessCommunication getUIWirelessCommunication(const std::string &filePath);
        static UIMessageQueues getUIMessageQueues(const std::string &filePath);
        static UISharedMemory getUISharedMemory(const std::string &filePath);
        static UICommunicationSystemParameters getUICommunicationProcessSystemParameters(const std::string &filePath);
        static std::vector<hardware::GPIO> getUISwitches(const std::string &filePath);
        // Setters
        static void setUICommunicationMode(const std::string &filePath, uint8_t processNumber, UICommunicationMode mode);

        /**** Feeder Commands ****/
        // Getters
        //static std::vector<config::AircraftParameters> getAircraftDatabase(const std::string &filePath);
        static FeederExecutableFiles getFeederExecutableFiles(const std::string &filePath);
        static FeederExternalWireless getFeederExternalWireless(const std::string &filePath);
        static FeederInternalWireless getFeederInternalWireless(const std::string &filePath);
        static FeederMessageQueues getFeederMessageQueues(const std::string &filePath);
        static FeederSharedMemory getFeederSharedMemory(const std::string &filePath);
        static FeederType getFeederType(const std::string &filePath);
        // Setters
        static void setFeederSystemValue(const std::string &filePath, FeederMode mode);

    private:
        static hardware::GPIOMode getGPIOMode(std::string mode);
        static hardware::GPIOPullMode getGPIOPullMode(std::string pullMode);
    };
}

#endif
