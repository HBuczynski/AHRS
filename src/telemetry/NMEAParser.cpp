#include <cstring>
#include <iostream>
#include "NMEAParser.h"

using namespace std;
using namespace gps;

uint8_t NMEAParser::validChecksum(const std::string &nmeaData)
{
    uint8_t sum = 0;
    uint16_t checksum = parseHex(nmeaData[nmeaData.size()-3]) * 16;
    checksum += parseHex(nmeaData[nmeaData.size()-2]);

    for(const auto& element : nmeaData)
    {
        if(element == '*')
            break;
        sum ^= element;
    }

    return static_cast<uint8_t>((sum =! checksum) ? 0 : 1);

}

uint8_t NMEAParser::parseHex(char c)
{
    if (c >= '0' && c <= '9')
        return static_cast<uint8_t>(c - '0');
    if (c >= 'A' && c <= 'F')
        return static_cast<uint8_t>(c - 'A' + 10);
    if (c >= 'a' && c <= 'f')
        return static_cast<uint8_t>(c - 'a' + 10);
    return 0;
}

SentenceType NMEAParser::getSentenceType(const std::string &nmeaData)
{
    if(nmeaData[0] != '$')
        return SentenceType::ERROR;

    if(!validChecksum(nmeaData))
        return SentenceType::ERROR;

    if(nmeaData.find(NMEA_GPGGA) != string::npos)
        return SentenceType::GPGGA;
    else if(nmeaData.find(NMEA_GPRMC) != string::npos)
        return SentenceType::GPRMC;
    else
        return SentenceType::ERROR;
}

void NMEAParser::parseGPRMCData(const std::string &nmeaData, GPSData &gpsData)
{

}

void NMEAParser::parseGPGGAData(const std::string &nmeaData, GPSData &gpsData)
{
    auto time = atoi(nmeaData.substr(NMEA_GPGGA_INIT_TIME_POSITION, NMEA_GPGGA_INIT_TIME_POSITION+6).c_str());
    gpsData.hour = time/10000;
    gpsData.minutes = (time % 10000) / 100;
    gpsData.seconds = time % 100;

    gpsData.latitude = atof(nmeaData.substr(NMEA_GPGGA_INIT_LATITUDE_POSITION, NMEA_GPGGA_INIT_TIME_POSITION + 9).c_str());
    gpsData.latitudeDirection = nmeaData[NMEA_GPGGA_INIT_LATITUDE_POSITION+10];
}
