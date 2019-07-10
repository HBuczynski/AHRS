#include "FlightDataManager.h"

#include <math.h>
#include <interfaces/wireless_measurement_commands/FeederData.h>
#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>

#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/BytesConverter.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;

FlightDataManager::FlightDataManager()
    : runAcquisition_(false),
      sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
{}

FlightDataManager::~FlightDataManager()
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- FlightDataManager :: Destructor.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    stopFlightDataTransmission();
}

bool FlightDataManager::isActive()
{
    return runAcquisition_;
}

void FlightDataManager::registerFun(std::function<bool(std::vector<uint8_t> )> broadcastFun)
{
    broadcastFunction_ = broadcastFun;
}

void FlightDataManager::startFlightDataTransmission()
{
    runAcquisition_ = true;
    acquisitionThread_ = thread(&FlightDataManager::sendMeasurements, this);

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOM- FlightDataManager :: Start sending measurements to cockpit.");
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
        const std::string message = std::string("-EXTCOM- FlightDataManager :: Stop sending measurements to cockpit.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void FlightDataManager::sendMeasurements()
{
    MeasuringDataFactory dataFactory;
    while (runAcquisition_)
    {
        try
        {
            auto frame = externalSharedMemory_->read();
            auto dataCommand = static_pointer_cast<FeederData, MeasuringData>(dataFactory.createCommand(frame));

            if(dataCommand->getMeasuringType() != MeasuringType::FLIGHT_DATA)
                break;

            if(!broadcastFunction_(dataCommand->getFrameBytes()))
            {
                runAcquisition_ = false;
                if(logger_.isInformationEnable() )
                {
                    const string message = string("-EXTCOM- FlightDataManager:: Broadcast is stopped, users are unavailable.");
                    logger_.writeLog(LogType::INFORMATION_LOG, message);
                }
            }
        }
        catch (exception &e)
        {
            if(logger_.isErrorEnable() )
            {
                const string message = string("-EXTCOM- FlightDataManager:: In catch function.");
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void FlightDataManager::initializeExternalSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-EXTCOMM- FlightDataManager:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-EXTCOMM- FlightDataManager :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
