#include <iostream>
#include <chrono>
#include <thread>
#include "../include/GPSAdafruitInterface.h"

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
        {
            lock_guard<mutex> lock(gpsDataMutex_);
            gpsData_.altitude = 234;
            gpsData_.course = 456;
        }
        this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

const GPSData &GPSAdafruitInterface::getData() const noexcept
{
    return gpsData_;
}

void GPSAdafruitInterface::interruptCallback(int gpio, int level, uint32_t tick, void *userdata)
{

}

void GPSAdafruitInterface::interruptHandle()
{

}

GPSStatus GPSAdafruitInterface::getStatus()
{
    return gpsStatus_;
}
