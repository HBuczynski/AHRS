#include "Common.h"
#include <config_reader/JSONParser.h>

using namespace std;
using namespace config;
using namespace common;

CommunicationParameters Common::getCommunicationParameters()
{
    CommunicationParameters parameters = {0};

    JSONParser parser("../../config/config.json");

    vector<string> configNames;
    configNames.push_back("CommunicationParameters");

    configNames.push_back("sourcePortUDP");
    parser.getUINT16t(configNames, parameters.sourcePortUDP);

    configNames.pop_back();
    configNames.push_back("sourceAddressUDP");
    parser.getString(configNames, parameters.sourceAddressUDP);

    configNames.pop_back();
    configNames.push_back("destinationPortTCP");
    parser.getUINT16t(configNames, parameters.destinationPortTCP);

    configNames.pop_back();
    configNames.push_back("destinationAddressTCP");
    parser.getString(configNames, parameters.destinationAddressTCP);

    return parameters;
}