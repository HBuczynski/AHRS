#include "ConfigurationReader.h"

using namespace std;
using namespace config;

std::unique_ptr<JSONParser> ConfigurationReader::jsonParser_;
CommunicationParameters ConfigurationReader::communicationParameters_;
CalibratedMagnetometers ConfigurationReader::calibratedMagnetometers_;
bool ConfigurationReader::dataWasRead_ = false;

ConfigurationReader::ConfigurationReader(const string &fileName)
{
    jsonParser_ = make_unique<JSONParser>(fileName);
}

ConfigurationReader::~ConfigurationReader()
{}

void ConfigurationReader::initialize()
{
    if(!dataWasRead_)
    {
        readCommunicationParameters();
        readCalibratedMagnetometersParameters();

        dataWasRead_ = true;
    }
}

void ConfigurationReader::readCommunicationParameters()
{

}

void ConfigurationReader::readCalibratedMagnetometersParameters()
{

}

const CommunicationParameters& ConfigurationReader::getCommunicationParameters()
{
    return communicationParameters_;
}

const CalibratedMagnetometers& ConfigurationReader::getCalibratedMagnetometersParameters()
{
    return calibratedMagnetometers_;
}