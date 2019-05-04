#ifndef IMUCALIBRATOR_H
#define IMUCALIBRATOR_H

#include <interfaces/wireless_responses/CalibratingStatusResponse.h>
#include <utility>
#include <atomic>
#include <mutex>

struct AccelCommon
{
    std::pair<bool, bool> x;
    std::pair<bool, bool> y;
    std::pair<bool, bool> z;
};

class IMUCalibrator
{
public:
    IMUCalibrator();

    void calibrateDevice();

    void enableAccelAxis(uint8_t axis);
    void disableAccelAxis(uint8_t axis);
    void approveAccelAxis(uint8_t axis);
    void nextAccelAxis();

    void approveMagnetometer();

    const communication::CalibrationConfiguration& getConfiguration();

private:
    void calibrateAccel();
    void calibrateAccelX();
    void calibrateAccelY();
    void calibrateAccelZ();

    void calibrateMag();

    void calibrateEll();
    void checkEllCondition();

    communication::CalibrationConfiguration config_;

    int8_t prevAxis_;
    int8_t currentAxis_;
    std::pair<bool, bool> axes[3]; // first - enable/disable; second - approve
    std::mutex mutex_;

    std::atomic<bool> accelIsDone_;
    std::atomic<bool> magIsDone_;
    std::atomic<bool> ellIsDone_;
};

#endif // IMUCALIBRATOR_H
