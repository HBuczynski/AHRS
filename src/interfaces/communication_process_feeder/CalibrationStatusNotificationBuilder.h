#ifndef AHRS_CALIBRATIONSTATUSNOTIFICATIONBUILDER_H
#define AHRS_CALIBRATIONSTATUSNOTIFICATIONBUILDER_H

#include "FeederNotificationBuilder.h"

namespace communication
{
    class CalibrationStatusNotificationBuilder final : public FeederNotificationBuilder
    {
    public:
        CalibrationStatusNotificationBuilder();
        ~CalibrationStatusNotificationBuilder();

        std::unique_ptr<FeederNotification> create(const std::vector<uint8_t> &commandInBytes) override;

    };
}

#endif