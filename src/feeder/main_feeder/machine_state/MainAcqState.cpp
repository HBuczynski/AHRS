#include "MainAcqState.h"
#include <math.h>

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
        //gpsAdafruit_.startAcq();
        acqThread_ = thread(&MainAcqState::runAcquisition, this);

        if (logger_.isInformationEnable())
        {
            const string message = string("-MAIN- MainAcqState:: Started acq thread.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
    }
    else
    {
        if (logger_.isInformationEnable())
        {
            const string message = string("-MAIN- MainAcqState:: Cannot start new acq thread.");
            logger_.writeLog(LogType::INFORMATION_LOG, message);
        }
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

bool MainAcqState::initializeDb(const std::string& name)
{
    feederDb_ = make_shared<database::FeederDb>(name);

    return feederDb_->openDb();
}

void MainAcqState::stopAcq()
{
    //gpsAdafruit_.stopAcq();

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
    int counter = 0;
    while(runAcq_)
    {
        try
        {
            planeOrientation_.readData();

            data.imuData = planeOrientation_.getImuData();
            //data.gpsData = gpsAdafruit_.getData();

            data.gpsData.altitude = 10000.0f + fabs(8000.0f * sin( counter * 34.0f / 923456.098f));
            data.gpsData.course = 450.0f + 300.0f * sin(counter / 1000);
            data.gpsData.fixQuality = 1;
            data.gpsData.groundSpeed = 50.0f + fabs(sin(counter / 9739.0f)) * 356;
            data.gpsData.latitude = 54.32 + fabs(sin(counter / 10000) * 568.0) / 100.0;
            data.gpsData.latitudeDirection = 'N';
            data.gpsData.longitude = 32.34 + fabs(sin(counter * 1927.0f / 98745.0f)) / 2345.0;
            data.gpsData.longitudeDirection = 'S';
            data.gpsData.numberOfSatellites = 6;
            data.gpsData.receiverWarning = 'A';
            data.gpsData.timestamp = utility::TimeManager::getImeSinceEpoch();

            counter++;

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

        this_thread::sleep_for(std::chrono::milliseconds(1));
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
    generalData.flightMeasurements.machNo = generalData.gpsData.groundSpeed  / 360.0f;
    generalData.flightMeasurements.pressure = 3;
    generalData.flightMeasurements.slipSkid = 2;
    generalData.flightMeasurements.turnCoordinator = sin(generalData.imuData.pitch / 23.0f)*4;
    generalData.flightMeasurements.verticalSpeed = 5.0f + sin(33.0f * generalData.imuData.pitch / 238.098f)*15.0f;
}

void MainAcqState::writeGeneralData(FeederGeneralData& generalData)
{

}

void MainAcqState::save2Database(FeederGeneralData& generalData)
{
    feederDb_->insertGPS(generalData.gpsData);
    feederDb_->insertIMU(generalData.imuData);
}
