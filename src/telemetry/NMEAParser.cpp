#include <cstring>
#include <iostream>
#include <iterator>
#include "NMEAParser.h"

#include <time_manager/TimeManager.h>

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
    string mark{","};
    const auto words = splitSentence(nmeaData, mark);

    gpsData.receiverWarning = words[2][0];
    gpsData.groundSpeed = stod(words[7])*KNOTS_TO_KMH;
    gpsData.course = stod(words[8]);
}

void NMEAParser::parseGPGGAData(const std::string &nmeaData, GPSData &gpsData)
{
    string mark{","};
    const auto words = splitSentence(nmeaData, mark);

    getTime(words[1], gpsData);
    getLatitude(words[2], words[3], gpsData);
    getLongitude(words[4], words[5], gpsData);

    gpsData.fixQuality = atoi(words[6].c_str());
    gpsData.numberOfSatellites = atoi(words[7].c_str());

    gpsData.altitude = stod(words[9]);
}

std::vector<std::string> NMEAParser::splitSentence(const std::string &sentence, const std::string &marks)
{
    vector<string> words;
    size_t begin, position = 0;

    while ( (begin = sentence.find_first_not_of(marks, position)) != string::npos)
    {
        position = sentence.find_first_of(marks, begin + 1);
        words.push_back(sentence.substr(begin, position - begin));
    }

    return words;
}

void NMEAParser::getTime(const string &time, GPSData &gpsData)
{
    gpsData.timestamp = utility::TimeManager::getImeSinceEpoch();
}

void NMEAParser::getLatitude(const string &latitude, string direction, GPSData &gpsData)
{
    gpsData.latitude = stod(latitude.substr(0,2));
    gpsData.latitude += stod(latitude.substr(2,5))/60;
    gpsData.latitudeDirection = direction[0];
}

void NMEAParser::getLongitude(const string &longitude, string direction, GPSData &gpsData)
{
    gpsData.longitude = stod(longitude.substr(0,3));
    gpsData.longitude += stod(longitude.substr(3,5))/60;
    gpsData.longitudeDirection = direction[0];
}
