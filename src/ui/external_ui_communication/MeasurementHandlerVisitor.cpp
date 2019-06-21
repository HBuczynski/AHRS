#include "MeasurementHandlerVisitor.h"

#include <iostream>

#include <interfaces/wireless_commands/UDPBitsCommand.h>
#include <config_reader/ConfigurationReader.h>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "CommunicationManagerUI.h"

using namespace std;
using namespace config;
using namespace utility;
using namespace communication;
using namespace boost::interprocess;

MeasurementHandlerVisitor::MeasurementHandlerVisitor(CommunicationManagerUI* communicationManagerUI)
    : communicationManagerUI_(communicationManagerUI),
      uiSharedMemoryParameters_(config::ConfigurationReader::getUISharedMemory(UI_PARAMETERS_FILE_PATH)),
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

    if(cockpitDb_->openDb())
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
                string(". Pitch: ") + to_string(data.getMeasurements().imuData.pitch) +
                string(". Latitude: ") + to_string(data.getMeasurements().gpsData.latitude) +
                string(". Altirude: ") + to_string(data.getMeasurements().gpsData.altitude);
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto frame = data.getFrameBytes();
    writeDataToSharedMemory(frame);
    this_thread::sleep_for(std::chrono::milliseconds(1));
}

void MeasurementHandlerVisitor::visit(UDPBitsData& data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("-ExtCOMM-MeasurementHandlerVisitor :: Received UDPBitsData.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto dataCommand = make_unique<UDPBitsCommand>();
    communicationManagerUI_->sendCommands(move(dataCommand));
}

void MeasurementHandlerVisitor::writeDataToSharedMemory(std::vector<uint8_t> &rawData)
{
    sharedMemory_->write(rawData);
}
