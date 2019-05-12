#include "MeasurementHandlerVisitor.h"

#include <iostream>
#include <config_reader/ConfigurationReader.h>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

MeasurementHandlerVisitor::MeasurementHandlerVisitor()
    : uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
{
    initializeSharedMemory();
}

MeasurementHandlerVisitor::~MeasurementHandlerVisitor()
{
}

void MeasurementHandlerVisitor::initializeDB(uint32_t hash, const std::string& name)
{
    cockpitDb_ = make_shared<database::CockpitDb>(name);
    auto isSuccess = cockpitDb_->openDb();

    FlightMeasurements flightMeasurements;

    flightMeasurements.pitch = 234;
    flightMeasurements.roll = 234;
    flightMeasurements.heading = 234;

    flightMeasurements.altitude = 234;
    flightMeasurements.groundSpeed = 346 ;
    flightMeasurements.latitude = 234;
    flightMeasurements.latitudeDirection = 234;
    flightMeasurements.longitude = 234;
    flightMeasurements.longitudeDirection = 234;
    flightMeasurements.groundSpeed = 234;

    //TODO:
    flightMeasurements.machNo = 345;
    flightMeasurements.pressure = 3;
    flightMeasurements.slipSkid = 2;
    flightMeasurements.turnCoordinator = 345;
    flightMeasurements.verticalSpeed = 15.0;

    cockpitDb_->insertFlightMeasurement(flightMeasurements);


    if(isSuccess)
    {
        if(logger_.isInformationEnable())
        {
            const string message = string("-ExtCOMM- MeasurementHandlerVisitor :: Opened DB, name: ") + name;
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-ExtCOMM- MeasurementHandlerVisitor :: Cannot open DB.");
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void MeasurementHandlerVisitor::initializeSharedMemory()
{
    try
    {
        // Creating shared memory.
        sharedMemory_ = make_unique<SharedMemoryWrapper>(uiSharedMemoryParameters_.sharedMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("-ExtCOMM-MeasurementHandlerVisitor :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void MeasurementHandlerVisitor::visit(ImuData &data)
{
    auto frame = data.getFrameBytes();
    writeDataToSharedMemory(frame);

    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM-MeasurementHandlerVisitor :: Received ImuData.") + to_string((data.getMeasurement()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MeasurementHandlerVisitor::visit(GpsData &data)
{
    auto frame = data.getFrameBytes();
    writeDataToSharedMemory(frame);

    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM-MeasurementHandlerVisitor :: Received GPSData.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MeasurementHandlerVisitor::visit(FeederData &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM-MeasurementHandlerVisitor :: Received ") + data.getName() +
                string(". Data: ") + to_string(data.getMeasurements().imuData.pitch);
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto frame = data.getFrameBytes();
    writeDataToSharedMemory(frame);

    const auto measurement = data.getMeasurements().flightMeasurements;
    cockpitDb_->insertFlightMeasurement(measurement);
}

void MeasurementHandlerVisitor::writeDataToSharedMemory(std::vector<uint8_t> &rawData)
{
    sharedMemory_->write(rawData);
}
