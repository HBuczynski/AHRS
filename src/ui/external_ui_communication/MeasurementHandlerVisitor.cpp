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
        // Creating shared memory's mutex.
        sharedMemoryMutex_ = make_unique<named_mutex>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str());
        // Creating shared memory.
        sharedMemory_ = make_unique<shared_memory_object>(open_only, uiSharedMemoryParameters_.sharedMemoryName.c_str(), read_write);
        // Mapped shared memory.
        mappedMemoryRegion_ = make_unique<mapped_region>(*sharedMemory_, read_write);
    }
    catch(interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("MainProcessScheduler :: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void MeasurementHandlerVisitor::visit(ImuData &data)
{
    saveDataToSharedMemory(data.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("MeasurementHandlerVisitor :: Received ImuData.") + to_string((data.getMeasurement()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MeasurementHandlerVisitor::visit(GpsData &data)
{
    saveDataToSharedMemory(data.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("MeasurementHandlerVisitor :: Received GPSData.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MeasurementHandlerVisitor::visit(FlightData &data)
{
    saveDataToSharedMemory(data.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("MeasurementHandlerVisitor :: Received ") + data.getName() +
                string(". Data: ") + to_string(data.getMeasurements().altitude);
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MeasurementHandlerVisitor::saveDataToSharedMemory(const std::vector<uint8_t> &rawData)
{
    uint8_t *pointerToMemory;
    {
        scoped_lock<named_mutex> lock(*sharedMemoryMutex_);
        pointerToMemory = reinterpret_cast<uint8_t*>(mappedMemoryRegion_->get_address());
        copy(rawData.begin(), rawData.end(), pointerToMemory);
    }
}


