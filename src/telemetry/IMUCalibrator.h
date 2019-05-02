#ifndef IMUCALIBRATOR_H
#define IMUCALIBRATOR_H

#include <config_reader/FeederParameters.h>
#include <shared_memory_wrapper/SharedMemoryWrapper.h>
#include <interfaces/wireless_responses/CalibratingStatusResponse.h>

#include <logger/Logger.h>
#include <string>

namespace telemetry
{
    class IMUCalibrator
    {
    public:
        IMUCalibrator();

        void startCalibration();

        void initializeExternalSharedMemory();
        void setPlane(const std::string& plane);

    private:

        config::FeederSharedMemory sharedMemoryParameters_;
        std::unique_ptr<communication::SharedMemoryWrapper> externalSharedMemory_;

        communication::CalibrationConfiguration calibrationConfiguration_;
        std::string planeName_;
        utility::Logger& logger_;
    };
}

#endif // IMUCALIBRATOR_H
