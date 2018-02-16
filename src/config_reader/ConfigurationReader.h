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
        ConfigurationReader(const std::string &fileName);
        ~ConfigurationReader();

        static void initialize();

        static const CommunicationParameters& getCommunicationParameters();
        static const CalibratedMagnetometers& getCalibratedMagnetometersParameters();

    private:
        static void readCommunicationParameters();
        static void readCalibratedMagnetometersParameters();

        static std::unique_ptr<JSONParser> jsonParser_;
        static bool dataWasRead_;

        static CommunicationParameters communicationParameters_;
        static CalibratedMagnetometers calibratedMagnetometers_;
    };
}

#endif