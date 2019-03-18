#include <iostream>
#include <chrono>
#include <thread>
#include "GPSAdafruitInterface.h"

using namespace std;
using namespace gps;

GPSAdafruitInterface::GPSAdafruitInterface(const std::string &deviceName)
    : rs232Interface_(deviceName)
{}

void GPSAdafruitInterface::initialize()
{
    rs232Interface_.initialize();

    string intervalUpdate(PMTK_SET_NMEA_UPDATE_10HZ);
    vector<uint8_t> intervalUpdateRaw(intervalUpdate.begin(), intervalUpdate.end());
    rs232Interface_.writeData(intervalUpdateRaw);

    //TODO: activate timer to check Fixed data
}

GPSData GPSAdafruitInterface::getData()
{
    GPSData gpsData{0};
    uint8_t status = 0;

    while (status != NMEA_COMPLETED)
    {
        const auto gpsPacket = rs232Interface_.readData();
        const auto gpsSentence = string(gpsPacket.begin(), gpsPacket.end());
        const auto sentenceType = NMEAParser::getSentenceType(gpsSentence);

        cout << gpsSentence << endl;

        switch (sentenceType)
        {
            case SentenceType::GPRMC :
            {
                NMEAParser::parseGPRMCData(gpsSentence, gpsData);
                status |= NMEA_GPGGA_STATUS;
                break;
            }
            case SentenceType::GPGGA :
            {
                NMEAParser::parseGPGGAData(gpsSentence, gpsData);
                status |= NMEA_GPRMC_STATUS;
                break;
            }
            default:
                break;
        }
    }
    return gpsData;
}

GPSStatus GPSAdafruitInterface::getStatus()
{
    return status_;
}
