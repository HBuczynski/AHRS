#include "FlightDataManager.h"

#include <interfaces/wireless_measurement_commands/FlightData.h>

using namespace std;
using namespace utility;
using namespace communication;

FlightDataManager::FlightDataManager(shared_ptr<ClientUDPManager> clientUDPManager)
    : runAcquisition_(false),
      clientUDPManager_(clientUDPManager),
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
    FlightMeasurements measurements;

    while (runAcquisition_)
    {
        measurements.verticalSpeed = 5.67;
        measurements.turnCoordinator = 5.67;
        measurements.longitude = 5.67;
        measurements.latitude = 5.67;
        measurements.heading = 5.67;
        measurements.groundSpeed = 5.67;
        measurements.altitude = 5.67;

        FlightData command(measurements);
        try
        {
            clientUDPManager_->broadcast(command.getFrameBytes());
        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable() )
            {
                const string message = string("FlightDataManager:: In catch function.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("FlightDataManager :: Outside loop.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
