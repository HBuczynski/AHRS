#ifndef GPS_TEST_NMEASENTENCE_H
#define GPS_TEST_NMEASENTENCE_H

#include <vector>
#include <cstdint>
#include <string>

namespace gps
{
    const std::string NMEA_GPRMC = "$GPRMC";
    const std::string NMEA_GPGGA = "$GPGGA";

    const uint8_t NMEA_GPRMC_STATUS = 0x01;
    const uint8_t NMEA_GPGGA_STATUS = 0x02;
    const uint8_t NMEA_COMPLETED = 0x03;

    const uint8_t NMEA_GPGGA_INIT_TIME_POSITION = 7;
    const uint8_t NMEA_GPGGA_INIT_LATITUDE_POSITION = 18;
    const uint8_t NMEA_GPGGA_INIT_LONGITUDE_POSITION = 7;

    enum class SentenceType
    {
        GPRMC,
        GPGGA,
        ERROR
    };

    struct GPSData
    {
        uint8_t hour;
        uint8_t minutes;
        uint8_t seconds;

        double latitude;
        char latitudeDirection;

        double longitude;
        char longitudeDirection;

        double altitude;

        uint8_t fixQuality;
        uint8_t numberOfSatellites;

        char receiverWarning;

        double groundSpeed;
        double course;
    };

    class NMEAParser
    {
    public:

        static uint8_t validChecksum(const std::string &nmeaData);
        static uint8_t parseHex(char c);

        static SentenceType getSentenceType(const std::string &nmeaData);

        static void parseGPRMCData(const std::string &nmeaData, GPSData &gpsData);

        static void parseGPGGAData(const std::string &nmeaData, GPSData &gpsData);
    };
}

#endif //GPS_TEST_NMEASENTENCE_H
