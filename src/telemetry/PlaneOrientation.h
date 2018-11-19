#ifndef AHRS_PLANEORIENTATION_H
#define AHRS_PLANEORIENTATION_H

#include <logger/Logger.h>

#include "RTIMUSettings.h"
#include "IMUDrivers/RTIMU.h"
#include "RTIMULibDefs.h"

namespace telemetry
{
    class PlaneOrientation
    {
    public:
        PlaneOrientation();
        ~PlaneOrientation();

        bool initDataAcquisition();
        void readData();

        float getPitch();
        float getRoll();
        float getYaw();

    private:
        RTIMUSettings *settings;
        RTIMU *imu;
        RTIMU_DATA imuData;

        utility::Logger& logger_;
    };
}

#endif
