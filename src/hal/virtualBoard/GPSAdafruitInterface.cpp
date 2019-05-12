#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

#include <time_manager/TimeManager.h>
#include <telemetry/NMEAParser.h>
#include "../include/GPSAdafruitInterface.h"

using namespace std;
using namespace gps;
using namespace utility;

bool GPSAdafruitInterface::initDone_ = false;

GPSAdafruitInterface::GPSAdafruitInterface(const std::string &deviceName)
    :   gpsData_({0}),
        fixedSwitch_(hardware::GPIO{23, hardware::GPIOMode::IN, hardware::GPIOPullMode::DOWN}),
        runAcq_(false),
        rs232Interface_(deviceName),
        gpsStatus_(GPSStatus::INITIALISED_TIME_EXCEED)
{}

GPSAdafruitInterface::~GPSAdafruitInterface()
{
   stopAcq();
}

void GPSAdafruitInterface::initialize()
{}

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
    int counter = 0;
    while(runAcq_)
    {
        {
            //TODO
            lock_guard<mutex> lock(gpsDataMutex_);
            gpsData_.altitude = 10000.0f + fabs(8000.0f * sin( counter * 34.0f / 923456.098f));
            gpsData_.course = 450.0f + 300.0f * sin(counter / 1000);
            gpsData_.fixQuality = 1;
            gpsData_.groundSpeed = 50.0f + fabs(sin(counter / 9739.0f)) * 356;
            gpsData_.latitude = 54.32 + fabs(sin(counter / 10000) * 568.0) / 100.0;
            gpsData_.latitudeDirection = 'N';
            gpsData_.longitude = 32.34 + fabs(sin(counter * 1927.0f / 98745.0f)) / 2345.0;
            gpsData_.longitudeDirection = 'S';
            gpsData_.numberOfSatellites = 6;
            gpsData_.receiverWarning = 'A';
            gpsData_.timestamp = utility::TimeManager::getImeSinceEpoch();

            counter++;
        }
        this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

const GPSData &GPSAdafruitInterface::getData() noexcept
{
    lock_guard<mutex> lock(gpsDataMutex_);
    return gpsData_;
}

void GPSAdafruitInterface::interruptCallback(int gpio, int level, uint32_t tick, void *userdata)
{}

void GPSAdafruitInterface::interruptHandle()
{}

GPSStatus GPSAdafruitInterface::getStatus()
{
    return gpsStatus_;
}
