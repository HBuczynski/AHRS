#include "IMUCalibrator.h"

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <config_reader/ConfigurationReader.h>
#include <utility/Utility.h>
#include <algorithm>

#include <RTIMUSettings.h>

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
    const auto dataset = Utility::getFilesNamesInDir(FEEDER_AIRCRAFTS_DATABASE_PATH);

    if(std::find(dataset.cbegin(), dataset.cend(), planeName_) != dataset.cend())
    {
        parseIniFile();
    }
    else
    {
        calibrationConfiguration_.progress = 0x07;
        calibrationConfiguration_.status = CalibrationStatus::IS_CALIBRATED;

        calibrationConfiguration_.accelerometer.mode = 1;
        calibrationConfiguration_.accelerometer.axis = 3;
        calibrationConfiguration_.accelerometer.maxX = 23;
        calibrationConfiguration_.accelerometer.maxY = 34;
        calibrationConfiguration_.accelerometer.maxZ = 34;
        calibrationConfiguration_.accelerometer.minX = 134;
        calibrationConfiguration_.accelerometer.minY = 45;
        calibrationConfiguration_.accelerometer.minZ = 34;

        calibrationConfiguration_.magnetometer.maxX = 54.05;
        calibrationConfiguration_.magnetometer.maxY = 54.05;
        calibrationConfiguration_.magnetometer.maxZ = 54.05;
        calibrationConfiguration_.magnetometer.minX = 54.05;
        calibrationConfiguration_.magnetometer.minY = 54.05;
        calibrationConfiguration_.magnetometer.minZ = 54.05;
    }

    CalibratingStatusResponse response(calibrationConfiguration_, 1);
    auto packet = response.getFrameBytes();

    cout << "IMU Calib: " << calibrationConfiguration_.magnetometer.maxX << endl;

    externalSharedMemory_->write(packet);
}

void IMUCalibrator::parseIniFile()
{
    const string path = config::FEEDER_AIRCRAFTS_DATABASE_PATH + planeName_;
    RTIMUSettings calibParam(path.c_str());

    calibParam.loadSettings();

    calibrationConfiguration_.progress = 0x07;
    calibrationConfiguration_.status = CalibrationStatus::IS_CALIBRATED;

    calibrationConfiguration_.accelerometer.mode = 1;
    calibrationConfiguration_.accelerometer.axis = 3;
    calibrationConfiguration_.accelerometer.maxX = calibParam.m_accelCalMax.x();
    calibrationConfiguration_.accelerometer.maxY = calibParam.m_accelCalMax.y();
    calibrationConfiguration_.accelerometer.maxZ = calibParam.m_accelCalMax.z();
    calibrationConfiguration_.accelerometer.minX = calibParam.m_accelCalMin.x();
    calibrationConfiguration_.accelerometer.minY = calibParam.m_accelCalMin.y();
    calibrationConfiguration_.accelerometer.minZ = calibParam.m_accelCalMin.z();

    calibrationConfiguration_.magnetometer.maxX = calibParam.m_compassCalMax.x();
    calibrationConfiguration_.magnetometer.maxY = calibParam.m_compassCalMax.y();
    calibrationConfiguration_.magnetometer.maxZ = calibParam.m_compassCalMax.z();
    calibrationConfiguration_.magnetometer.minX = calibParam.m_compassCalMin.x();
    calibrationConfiguration_.magnetometer.minY = calibParam.m_compassCalMin.y();
    calibrationConfiguration_.magnetometer.minZ = calibParam.m_compassCalMin.z();

    calibrationConfiguration_.ellipsoid.mode = 1;
    calibrationConfiguration_.ellipsoid.quadrant_11 = calibParam.m_compassCalEllipsoidCorr[0][0];
    calibrationConfiguration_.ellipsoid.quadrant_12 = calibParam.m_compassCalEllipsoidCorr[0][1];
    calibrationConfiguration_.ellipsoid.quadrant_13 = calibParam.m_compassCalEllipsoidCorr[0][2];
    calibrationConfiguration_.ellipsoid.quadrant_21 = calibParam.m_compassCalEllipsoidCorr[1][0];
    calibrationConfiguration_.ellipsoid.quadrant_22 = calibParam.m_compassCalEllipsoidCorr[1][1];
    calibrationConfiguration_.ellipsoid.quadrant_23 = calibParam.m_compassCalEllipsoidCorr[1][2];
    calibrationConfiguration_.ellipsoid.quadrant_31 = calibParam.m_compassCalEllipsoidCorr[2][0];
    calibrationConfiguration_.ellipsoid.quadrant_32 = calibParam.m_compassCalEllipsoidCorr[2][1];
    calibrationConfiguration_.ellipsoid.quadrant_33 = calibParam.m_compassCalEllipsoidCorr[2][2];
}
