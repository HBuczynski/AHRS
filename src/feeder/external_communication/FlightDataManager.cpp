#include "FlightDataManager.h"

#include <math.h>
#include <interfaces/wireless_measurement_commands/FlightData.h>

using namespace std;
using namespace utility;
using namespace communication;

FlightDataManager::FlightDataManager(function<bool(vector<uint8_t> )> broadcastFun)
    : runAcquisition_(false),
      broadcastFunction_(broadcastFun),
      logger_(Logger::getInstance())
{}

FlightDataManager::~FlightDataManager()
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("FlightDataManager :: Destructor.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    stopFlightDataTransmission();
}

void FlightDataManager::startFlightDataTransmission()
{
    runAcquisition_ = true;

    if(acquisitionThread_.joinable())
    {
        acquisitionThread_.join();
    }
    acquisitionThread_ = thread(&FlightDataManager::sendMeasurements, this);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("FlightDataManager :: Start sending measurements to cockpit.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void FlightDataManager::stopFlightDataTransmission()
{
    runAcquisition_ = false;

    if (acquisitionThread_.joinable())
    {
        acquisitionThread_.join();
    }

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("FlightDataManager :: Stop sending measurements to cockpit.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void FlightDataManager::sendMeasurements()
{
    uint64_t counter = 0;

    while (runAcquisition_)
    {
        ++counter;
        FlightMeasurements measurements;
        measurements.roll      =  180.0f * sin( counter / 9000.0f );
        measurements.pitch     =   90.0f * sin( counter /  20000.0f );
        measurements.heading   =  360.0f * sin( counter /  4000.0f );
        measurements.slipSkid  =    1.0f * sin( counter /  1000.0f );
        measurements.turnCoordinator  =    7.0f * sin( counter /  1000.0f )/6.0f;
        measurements.groundSpeed  =  125.0f * sin( counter /  4000.0f ) +  125.0f;
        measurements.altitude  = 9000.0f * sin( counter /  4000.0f ) + 9000.0f;
        measurements.pressure  =    2.0f * sin( counter /  2000.0f ) +   30.0f;
        measurements.verticalSpeed =  650.0f * sin( counter /  2000.0f )/100.0f;
        measurements.machNo    = measurements.groundSpeed / 650.0f;

        if(logger_.isInformationEnable() )
        {
            const string message = string("FlightDataManager:: Roll: ") + to_string(measurements.roll) + string(" Counter: ") + to_string(counter);
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }

        FlightData command(measurements);
        try
        {
            if(!broadcastFunction_(command.getFrameBytes()))
            {
                runAcquisition_ = false;
                if(logger_.isInformationEnable() )
                {
                    const string message = string("FlightDataManager:: Broadcast is stopped, users are unavailable.");
                    logger_.writeLog(LogType::INFORMATION_LOG, message);
                }
            }
        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable() )
            {
                const string message = string("FlightDataManager:: In catch function.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}
