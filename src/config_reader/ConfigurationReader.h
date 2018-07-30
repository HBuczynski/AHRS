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

        static FeederParameters getFeederParameters(const std::string &filePath);
        static UIParameters getUIParameters(const std::string &filePath);
    };
}

#endif