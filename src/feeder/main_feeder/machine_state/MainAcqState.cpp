#include "MainAcqState.h"

#include <interfaces/wireless_measurement_commands/FeederData.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/BytesConverter.h>

using namespace std;
using namespace config;
using namespace utility;
using namespace telemetry;
using namespace communication;
using namespace boost::interprocess;

extern char **environ;

bool MainAcqState::initialization_ = false;

MainAcqState::MainAcqState(const std::string &name, std::shared_ptr<State> parent)
    : State(name, parent),
      gpsAdafruit_("/dev/ttyUSB0"),
      runAcq_(false),
      sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH))
{}

void MainAcqState::registerDataCallback(std::function<FeederDataContainer&()> getFeederData)
{
    getFeederData_ = getFeederData;
}

void MainAcqState::runEntryEvent()
{}

void MainAcqState::runExitEvent()
{
    stopAcq();

    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- MainAcqState:: Exit event.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MainAcqState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("-MAIN- MainAcqState:: Invoke procedure for - ") + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    bool isSuccess = true;

    if(!initialization_)
    {
        isSuccess = initializeExternalSharedMemory();
        isSuccess = isSuccess && planeOrientation_.initDataAcquisition(getFeederData_().planeName);
    }

    if(isSuccess)
    {
        runAcq_ = true;
        gpsAdafruit_.startAcq();
        acqThread_ = thread(&MainAcqState::runAcquisition, this);
    }
}

bool MainAcqState::initializeExternalSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- MainAcqState:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- MainAcqState:: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

void MainAcqState::stopAcq()
{
    gpsAdafruit_.stopAcq();

    runAcq_ = false;

    if(acqThread_.joinable())
    {
        acqThread_.join();
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- MainAcqState:: Stop acq.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MainAcqState::runAcquisition()
{
    FeederGeneralData data;
    while(runAcq_)
    {
        try
        {
            planeOrientation_.readData();

            data.imuData = planeOrientation_.getImuData();
            data.gpsData = gpsAdafruit_.getData();

            calculateFlightParameters(data);
            writeGeneralData(data);
            save2Database(data);

            FeederData dataCommand(data);
            auto packet = dataCommand.getFrameBytes();
            externalSharedMemory_->write(packet);
        }
        catch(interprocess_exception &ex)
        {
            if (logger_.isErrorEnable())
            {
               const std::string message = std::string("-MAIN- MainAcqState:: External SharedMemory: ") + ex.what();
               logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void MainAcqState::calculateFlightParameters(FeederGeneralData& generalData)
{
    generalData.flightMeasurements.pitch = generalData.imuData.pitch;
    generalData.flightMeasurements.roll = generalData.imuData.roll;
    generalData.flightMeasurements.heading = generalData.imuData.yaw;

    generalData.flightMeasurements.altitude = generalData.gpsData.altitude;
    generalData.flightMeasurements.groundSpeed = generalData.gpsData.groundSpeed;
    generalData.flightMeasurements.latitude = generalData.gpsData.latitude;
    generalData.flightMeasurements.latitudeDirection = generalData.gpsData.latitudeDirection;
    generalData.flightMeasurements.longitude = generalData.gpsData.longitude;
    generalData.flightMeasurements.longitudeDirection = generalData.gpsData.longitudeDirection;
    generalData.flightMeasurements.groundSpeed = generalData.gpsData.groundSpeed;

    //TODO:
    generalData.flightMeasurements.machNo = 0.45;
    generalData.flightMeasurements.pressure = 456;
    generalData.flightMeasurements.slipSkid = 896;
    generalData.flightMeasurements.turnCoordinator = 23;
    generalData.flightMeasurements.verticalSpeed = 23;
}

void MainAcqState::writeGeneralData(FeederGeneralData& generalData)
{

}

void MainAcqState::save2Database(FeederGeneralData& generalData)
{
//TODO
}
