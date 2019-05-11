#ifndef AHRS_PLANEORIENTATION_H
#define AHRS_PLANEORIENTATION_H

#include <common/Measurements.h>
#include <logger/Logger.h>
#include <memory>

#include "IMUDrivers/RTIMU.h"
#include "RTIMUSettings.h"
#include "RTIMULibDefs.h"

namespace telemetry
{
    class PlaneOrientationHandler
    {
    public:
        PlaneOrientationHandler();
        ~PlaneOrientationHandler();

        bool initDataAcquisition(const std::string& planeName);
        void readData();

        const IMUData& getImuData();

    private:
        uint64_t counter_;
        RTIMUSettings* settings_;
        RTIMU* imu_;
        RTIMU_DATA rtImuData_;

        IMUData imuData_;
        utility::Logger& logger_;
    };
}

#endif
