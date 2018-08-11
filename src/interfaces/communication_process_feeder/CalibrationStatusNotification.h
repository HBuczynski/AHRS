#ifndef AHRS_CALIBRATIONSTATUSNOTIFICATION_H
#define AHRS_CALIBRATIONSTATUSNOTIFICATION_H

#include "FeederNotification.h"

namespace communication
{
    enum CalibrationStatus : uint8_t
    {
        PASSED = 0x01,
        FAILED = 0x02,
        IN_THE_PROCESS = 0x03
    };

    class CalibrationStatusNotification final : public FeederNotification
    {
    public:
        CalibrationStatusNotification(CalibrationStatus status);
        ~CalibrationStatusNotification();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(FeederNotificationVisitor& visitor) override;

        CalibrationStatus getCalibrationStatus() const;
        void setCalibrationStatus(CalibrationStatus status);

    private:
        virtual void initializeDataSize() override;

        CalibrationStatus status_;

    };
}

#endif
