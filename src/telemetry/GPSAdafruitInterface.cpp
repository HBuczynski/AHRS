#include <iostream>
#include <chrono>
#include <thread>
#include "GPSAdafruitInterface.h"

using namespace std;
using namespace gps;

GPSAdafruitInterface::GPSAdafruitInterface(const std::string &deviceName)
    :   fixedSwitch_(hardware::GPIO{23, hardware::GPIOMode::IN, hardware::GPIOPullMode::DOWN}),
        rs232Interface_(deviceName),
        gpsStatus_(GPSStatus::INITIALISED_TIME_EXCEED)
{}

void GPSAdafruitInterface::initialize()
{
    rs232Interface_.initialize();

    string intervalUpdate(PMTK_SET_NMEA_UPDATE_10HZ);
    vector<uint8_t> intervalUpdateRaw(intervalUpdate.begin(), intervalUpdate.end());
    rs232Interface_.writeData(intervalUpdateRaw);

    gpsStatus_ = GPSStatus::SEARCHING_SATELLITES;

    start_ = std::chrono::system_clock::now();
    fixedSwitch_.registerHandler(interruptCallback, RISING_EDGE, 0, reinterpret_cast<void *>(this));
}

GPSData GPSAdafruitInterface::getData()
{
    GPSData gpsData{0};

    if(gpsStatus_ == GPSStatus::FIXED)
    {
        uint8_t status = 0;
        while (status != NMEA_COMPLETED)
        {
            const auto gpsPacket = rs232Interface_.readData();
            const auto gpsSentence = string(gpsPacket.begin(), gpsPacket.end());

            if(gpsSentence.size() < SENTENCE_MIN_THRESHOLD)
                continue;

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
    }

    return gpsData;
}

void GPSAdafruitInterface::interruptCallback(int gpio, int level, uint32_t tick, void *userdata)
{
    GPSAdafruitInterface* handle = reinterpret_cast<GPSAdafruitInterface*>(userdata);
    handle->interruptHandle();
}

void GPSAdafruitInterface::interruptHandle()
{
    end_ = std::chrono::system_clock::now();
    uint32_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();

    cout << "In interrupt handler\t";
    cout << "Duration: " << duration << endl;

    if(duration > FIXED_THRESHOLD)
    {
        gpsStatus_ = GPSStatus::FIXED;
    }
    else
    {
        gpsStatus_ = GPSStatus::SEARCHING_SATELLITES;
    }

    start_ = end_;
}

GPSStatus GPSAdafruitInterface::getStatus()
{
    return gpsStatus_;
}
