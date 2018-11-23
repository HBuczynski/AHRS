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

        RTQuaternion m_gravity;
        RTQuaternion rotatedGravity;
        RTQuaternion fusedConjugate;
        RTQuaternion qTemp;
        RTVector3 residuals;

        float prevX;
        float prevY;
        float prevZ;

        utility::Logger& logger_;
    };
}

#endif
