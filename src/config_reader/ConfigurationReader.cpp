#include "ConfigurationReader.h"

using namespace std;
using namespace config;

ConfigurationReader::ConfigurationReader()
{}

ConfigurationReader::~ConfigurationReader()
{}

CommunicationParameters ConfigurationReader::getWirelessParameters(const std::string &path)
{
    JSONParser jsonParser(path);
    CommunicationParameters communicationParameters;

    vector<string> configNames;
    configNames.push_back("WirelessParameters");

    configNames.push_back("sourcePortUDP");
    jsonParser.getUINT16t(configNames, communicationParameters.sourcePortUDP);

    configNames.pop_back();
    configNames.push_back("sourceAddressUDP");
    jsonParser.getString(configNames, communicationParameters.sourceAddressUDP);

    configNames.pop_back();
    configNames.push_back("destinationPortTCP");
    jsonParser.getUINT16t(configNames, communicationParameters.destinationPortTCP);

    configNames.pop_back();
    configNames.push_back("destinationAddressTCP");
    jsonParser.getString(configNames, communicationParameters.destinationAddressTCP);

    return communicationParameters;
}

CalibratedMagnetometers ConfigurationReader::getCalibratedMagnetometersParameters(const std::string& path)
{
    CalibratedMagnetometers calibratedMagnetometers;

    return calibratedMagnetometers;
}