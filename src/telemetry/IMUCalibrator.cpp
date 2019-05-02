#include "IMUCalibrator.h"

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
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

IMUCalibrator::IMUCalibrator()
    : sharedMemoryParameters_(ConfigurationReader::getFeederSharedMemory(FEEDER_PARAMETERS_FILE_PATH)),
      logger_(Logger::getInstance())
{}

void IMUCalibrator::setPlane(const std::string& plane)
{
    planeName_ = plane;
}

void IMUCalibrator::initializeExternalSharedMemory()
{
    try
    {
        externalSharedMemory_ = std::make_unique<SharedMemoryWrapper>(sharedMemoryParameters_.externalMemoryName);
    }
    catch(interprocess_exception &ex)
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = std::string("-MAIN- IMUCalibrator:: External SharedMemory: ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("-MAIN- IMUCalibrator :: External shared memory has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void IMUCalibrator::startCalibration()
{
    calibrationConfiguration_.status = CalibrationStatus::START_CALIBARTION;
    calibrationConfiguration_.progress = 0x01;
    calibrationConfiguration_.accelerometer.axis = 1;
    calibrationConfiguration_.accelerometer.mode = 1;
    calibrationConfiguration_.accelerometer.maxX = 45.9876;
    calibrationConfiguration_.accelerometer.maxY = 45.9876;
    calibrationConfiguration_.accelerometer.maxZ = 35.9876;

    calibrationConfiguration_.accelerometer.minX = 555.9876;
    calibrationConfiguration_.accelerometer.minY = 545.9876;
    calibrationConfiguration_.accelerometer.minZ = 508.9876;

    calibrationConfiguration_.ellipsoid.mode = 0;

    CalibratingStatusResponse response(calibrationConfiguration_, 1);
    auto packet = response.getFrameBytes();

    externalSharedMemory_->write(packet);
}
