#ifndef AHRS_CONFIGURATIONREADER_H
#define AHRS_CONFIGURATIONREADER_H

#include "JSONParser.h"
#include "Parameters.h"
#include <memory>

namespace config
{
    class ConfigurationReader
    {
    public:
        ConfigurationReader();
        ~ConfigurationReader();

        static CommunicationParameters getCommunicationParameters(const std::string& filePath);
        static CalibratedMagnetometers getCalibratedMagnetometersParameters(const std::string& filePath);
    };
}

#endif