#include "MainAcqState.h"
#include <math.h>

#include <interfaces/wireless_measurement_commands/MeasuringDataFactory.h>
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
      previousTime_(0),
      previousAltitude_(0),
      previousVerticalVelocity_(0),
      gpsAdafruit_(FEEDER_GPS_DEVICE_FILE),
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
        isSuccess = isSuccess && initializeInternalSharedMemory();
        isSuccess = isSuccess && planeOrientation_.initDataAcquisition(getFeederData_().planeName);
        isSuccess = isSuccess && gpsAdafruit_.initialize();
    }

    if(isSuccess)
    {
        runAcq_ = true;
        runDB_ = true;

        gpsAdafruit_.startAcq();
        acqThread_ = thread(&MainAcqState::runAcquisition, this);

        dbThread_ = thread(&MainAcqState::save2Database, this);

        if (logger_.isInformationEnable())
        {
            const string message = string("-MAIN- MainAcqState:: Started acq thread. Mode: ") + to_string(static_cast<int>(ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH).mode));
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


bool MainAcqState::initializeInternalSharedMemory()
{
    try
    {
        internalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.internalMemoryName);
        internalSharedMemory_->clear();
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- MainAcqState:: Internal SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- MainAcqState:: Internal shared memory has been initialized correctly.");
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
    gpsAdafruit_.stopAcq();

    runAcq_ = false;
    runDB_ = false;

    if(dbThread_.joinable())
        dbThread_.join();

    if(acqThread_.joinable())
        acqThread_.join();

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- MainAcqState:: Stop acq.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MainAcqState::runAcquisition()
{
    FeederGeneralData data;
    FeederMode feederMode = ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH).mode;

    while(runAcq_)
    {
        try
        {
            planeOrientation_.readData();

            data.imuData = planeOrientation_.getImuData();
            data.gpsData = gpsAdafruit_.getData();

            calculateFlightParameters(data);

            FeederData dataCommand(data);
            auto packet = dataCommand.getFrameBytes();

            if (feederMode == FeederMode::MASTER)
                externalSharedMemory_->write(packet);
            else
                internalSharedMemory_->write(packet);
        }
        catch(interprocess_exception &ex)
        {
            if (logger_.isErrorEnable())
            {
               const std::string message = std::string("-MAIN- MainAcqState:: External SharedMemory: ") + ex.what();
               logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}

void MainAcqState::calculateFlightParameters(FeederGeneralData& generalData)
{
    generalData.flightMeasurements.timestamp = generalData.gpsData.timestamp;
    generalData.flightMeasurements.pitch =  generalData.imuData.pitch;
    generalData.flightMeasurements.roll = generalData.imuData.roll;
    generalData.flightMeasurements.heading = generalData.imuData.yaw;

    generalData.flightMeasurements.altitude = generalData.gpsData.altitude;

    generalData.flightMeasurements.groundSpeed = generalData.gpsData.groundSpeed;
    generalData.flightMeasurements.latitude = generalData.gpsData.latitude;
    generalData.flightMeasurements.latitudeDirection = generalData.gpsData.latitudeDirection;
    generalData.flightMeasurements.longitude = generalData.gpsData.longitude;
    generalData.flightMeasurements.longitudeDirection = generalData.gpsData.longitudeDirection;

    // TO DO:
    generalData.flightMeasurements.machNo = calculateMachNo(generalData.gpsData.groundSpeed, generalData.gpsData.altitude);
    generalData.flightMeasurements.pressure = 0;
    generalData.flightMeasurements.slipSkid = 0;
    generalData.flightMeasurements.turnCoordinator = generalData.imuData.roll / 25.0;

    /* units: m/s */
    if(generalData.flightMeasurements.timestamp - previousTime_ >= 2)
    {
        generalData.flightMeasurements.verticalSpeed = (generalData.gpsData.altitude - previousAltitude_) / (generalData.flightMeasurements.timestamp - previousTime_);
        previousTime_ = generalData.flightMeasurements.timestamp;
        previousAltitude_ = generalData.flightMeasurements.altitude;
    }
}

double MainAcqState::calculateMachNo(double velocity, double altitude)
{
    double a_0 = 340.3; // m/s
    double t_0 = 288.15; // Kelwins

    double t = t_0 - 6.5*altitude / 1000.0;

    double a = a_0*sqrt(t/288.0);

    return velocity / a;
}

void MainAcqState::save2Database()
{
    communication::MeasuringDataFactory dataFactory_;
    FeederMode feederMode = ConfigurationReader::getFeederType(FEEDER_TYPE_FILE_PATH).mode;
    vector<uint8_t> frame;

    while(runDB_)
    {
        try
        {
            if (feederMode == FeederMode::MASTER)
                frame = externalSharedMemory_->read();
            else
                frame = internalSharedMemory_->read();

            if(frame.size() != 0)
            {
                auto flightData = static_pointer_cast<communication::FeederData, communication::MeasuringData>(
                        dataFactory_.createCommand(frame));

                const auto measurements = flightData->getMeasurements();

                feederDb_->insertGPS(measurements.gpsData);
                feederDb_->insertIMU(measurements.imuData);
            }
        }
        catch (exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("-MAIN- MainAcqState:: Saving into Database - ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
