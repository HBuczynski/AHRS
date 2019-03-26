#ifndef AHRS_PLANEORIENTATION_H
#define AHRS_PLANEORIENTATION_H

#include <logger/Logger.h>
#include <memory>

#include "IMUDrivers/RTIMU.h"
#include "RTIMUSettings.h"
#include "RTIMULibDefs.h"

namespace telemetry
{
    class PlaneOrientation
    {
    public:
        PlaneOrientation();
        ~PlaneOrientation();

        bool initDataAcquisition(const std::string& planeName);
        void readData();

        float getPitch();
        float getRoll();
        float getYaw();

    private:
        RTIMUSettings* settings_;
        RTIMU* imu_;
        RTIMU_DATA imuData_;

        utility::Logger& logger_;
    };
}

#endif
