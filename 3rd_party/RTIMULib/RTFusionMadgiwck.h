#ifndef AHRS_RTFUSIONMADGIWCK_H
#define AHRS_RTFUSIONMADGIWCK_H

#include "RTFusion.h"
#include <logger/Logger.h>

class RTFusionMadgiwck : public RTFusion
{
public:
    RTFusionMadgiwck();
    ~RTFusionMadgiwck();

    //  fusionType returns the type code of the fusion algorithm

    virtual int fusionType() { return RTFUSION_TYPE_MADGWICK; }

    //  reset() resets the kalman state but keeps any setting changes (such as enables)
    void reset();

    //  newIMUData() should be called for subsequent updates
    //  deltaTime is in units of seconds
    void newIMUData(RTIMU_DATA& data, const RTIMUSettings *settings);
    void begin(float sampleFrequency) { invSampleFreq = 1.0f / sampleFrequency; }

private:

    void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    static float invSqrt(float x);
    void computeAngles();

    float beta;				// algorithm gain
    float q0;
    float q1;
    float q2;
    float q3;	// quaternion of sensor frame relative to auxiliary frame
    float invSampleFreq;
    float roll;
    float pitch;
    float yaw;

    utility::Logger& logger_;
};

#endif //AHRS_RTFUSIONMADGIWCK_H
