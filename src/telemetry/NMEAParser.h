#ifndef GPS_TEST_NMEASENTENCE_H
#define GPS_TEST_NMEASENTENCE_H

#include <vector>
#include <cstdint>
#include <string>

#include <common/Measurements.h>

namespace gps
{
    const std::string NMEA_GPRMC = "$GPRMC";
    const std::string NMEA_GPGGA = "$GPGGA";

    const double KNOTS_TO_KMH = 1.852;

    const uint8_t NMEA_GPRMC_STATUS = 0x01;
    const uint8_t NMEA_GPGGA_STATUS = 0x02;
    const uint8_t NMEA_COMPLETED = 0x03;

    enum class SentenceType
    {
        GPRMC,
        GPGGA,
        ERROR
    };


    class NMEAParser
    {
    public:

        static uint8_t validChecksum(const std::string &nmeaData);
        static uint8_t parseHex(char c);

        static SentenceType getSentenceType(const std::string &nmeaData);

        static void parseGPRMCData(const std::string &nmeaData, GPSData &gpsData);

        static void parseGPGGAData(const std::string &nmeaData, GPSData &gpsData);

    private:
        static std::vector<std::string> splitSentence(const std::string& sentence, const std::string &marks);

        static void getTime(const std::string& time, GPSData &gpsData);
        static void getLatitude(const std::string &latitude, std::string direction, GPSData &gpsData);
        static void getLongitude(const std::string &longitude, std::string direction, GPSData &gpsData);


        static void getSatellitesProperties(const std::string& sentence, GPSData &gpsData);


    };
}

#endif //GPS_TEST_NMEASENTENCE_H
