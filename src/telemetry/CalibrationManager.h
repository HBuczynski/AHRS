#ifndef CALIBRATION_MANAGER_H
#define CALIBRATION_MANAGER_H

#include <config_reader/FeederParameters.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <interfaces/wireless_commands/CalibrateAccelerometerCommand.h>

#include <hal/include/IMUCalibrator.h>

#include <logger/Logger.h>
#include <thread>
#include <string>
#include <atomic>

namespace telemetry
{
    class CalibrationManager
    {
    public:
        CalibrationManager();

        void startCalibration();
        void stopCalibration();

        void initializeExternalSharedMemory();
        void setPlane(const std::string& plane);

        void accelerometerAction(uint8_t axis, communication::AccelAction action);
        void approveMagnetometer();

    private:
        void parseIniFile();
        void run();

        void saveInMemory(const communication::CalibrationConfiguration& config);

        IMUCalibrator imuCalibrator_;

        std::atomic<bool> runCalibration_;
        std::thread calibrationThread_;

        config::FeederSharedMemory sharedMemoryParameters_;
        std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;

        std::string planeName_;

        utility::Logger& logger_;
    };
}

#endif
