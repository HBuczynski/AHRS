#include "DataHandlerVisitor.h"

#include <iostream>
#include <common/InterprocessData.h>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace std;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

DataHandlerVisitor::DataHandlerVisitor()
    : logger_(Logger::getInstance())
{
    initializeSharedMemory();
}

DataHandlerVisitor::~DataHandlerVisitor()
{}

void DataHandlerVisitor::initializeSharedMemory()
{
    try
    {
        // Creating shared memory's mutex.
        sharedMemoryMutex_ = make_unique<named_mutex>(open_only, SHARED_MEMORY_MUTEX_NAME.c_str());
        // Creating shared memory.
        sharedMemory_ = make_unique<shared_memory_object>(open_only, SHARED_MEMORY_NAME.c_str(), read_write);
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

void DataHandlerVisitor::visit(ImuData &data)
{
    saveDataToSharedMemory(data.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("DataHandlerVisitor :: Received ImuData.") + to_string((data.getMeasurement()));
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void DataHandlerVisitor::visit(GpsData &data)
{
    saveDataToSharedMemory(data.getFrameBytes());

    if(logger_.isInformationEnable())
    {
        const string message = string("DataHandlerVisitor :: Received GPSData.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void DataHandlerVisitor::saveDataToSharedMemory(const std::vector<uint8_t> &rawData)
{
    uint8_t *pointerToMemory;
    {
        scoped_lock<named_mutex> lock(*sharedMemoryMutex_);
        pointerToMemory = reinterpret_cast<uint8_t*>(mappedMemoryRegion_->get_address());
        copy(rawData.begin(), rawData.end(), pointerToMemory);
    }
}
