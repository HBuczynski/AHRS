#include <iostream>
#include <chrono>
#include <thread>
#include "../include/GPSAdafruitInterface.h"

#include <telemetry/NMEAParser.h>

using namespace std;
using namespace gps;

GPSAdafruitInterface::GPSAdafruitInterface(const std::string &deviceName)
    :   fixedSwitch_(hardware::GPIO{23, hardware::GPIOMode::IN, hardware::GPIOPullMode::DOWN}),
        runAcq_(false),
        rs232Interface_(deviceName),
        gpsStatus_(GPSStatus::INITIALISED_TIME_EXCEED)
{}

GPSAdafruitInterface::~GPSAdafruitInterface()
{
   stopAcq();
}

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

void GPSAdafruitInterface::startAcq()
{
    runAcq_ = true;
    acqThread_ = thread(&GPSAdafruitInterface::dataAcq, this);
}

void GPSAdafruitInterface::stopAcq()
{
    runAcq_ = false;

    if(acqThread_.joinable())
        acqThread_.join();
}

void GPSAdafruitInterface::dataAcq()
{
    while(runAcq_)
    {
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

                switch (sentenceType)
                {
                    case SentenceType::GPRMC :
                    {
                        {
                            lock_guard<mutex> lock(gpsDataMutex_);
                            NMEAParser::parseGPRMCData(gpsSentence, gpsData_);  
                        }
                        status |= NMEA_GPGGA_STATUS;
                        break;
                    }
                    case SentenceType::GPGGA :
                    {
                        {
                            lock_guard<mutex> lock(gpsDataMutex_);
                            NMEAParser::parseGPGGAData(gpsSentence, gpsData_);
                        }
                        status |= NMEA_GPRMC_STATUS;
                        break;
                    }
                    default:
                        break;
                }
            }
        }F

        this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

const GPSData &GPSAdafruitInterface::getData() const noexcept
{
    return gpsData_;
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
