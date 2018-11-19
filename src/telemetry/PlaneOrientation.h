#ifndef AHRS_PLANEORIENTATION_H
#define AHRS_PLANEORIENTATION_H

#include <logger/Logger.h>

#include "../../3rd_party/RTIMULib/RTIMUSettings.h"
#include "../../3rd_party/RTIMULib/IMUDrivers/RTIMU.h"
#include "../../3rd_party/RTIMULib/RTIMULibDefs.h"

namespace telemetry
{
    class PlaneOrientation
    {
    public:
        PlaneOrientation();
        ~PlaneOrientation();

        void initDataAcquisition();

        void readData();

        float getPitch();
        float getRoll();
        float getYaw();

    private:

        int sampleCount;
        int sampleRate;
        uint64_t rateTimer;
        uint64_t displayTimer;
        uint64_t now_;

        RTIMUSettings *settings;
        RTIMU *imu;
        RTIMU_DATA imuData;

        utility::Logger& logger_;
    };
}

#endif
