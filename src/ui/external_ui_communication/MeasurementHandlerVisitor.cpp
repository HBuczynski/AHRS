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
{}

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

void MeasurementHandlerVisitor::visit(FlightData &data)
{
    auto frame = data.getFrameBytes();
    writeDataToSharedMemory(frame);

    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM-MeasurementHandlerVisitor :: Received ") + data.getName() +
                string(". Data: ") + to_string(data.getMeasurements().altitude);
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MeasurementHandlerVisitor::writeDataToSharedMemory(std::vector<uint8_t> &rawData)
{
    sharedMemory_->write(rawData);
}


