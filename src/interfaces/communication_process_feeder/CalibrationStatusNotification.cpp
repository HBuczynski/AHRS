#include "CalibrationStatusNotification.h"
#include "FeederNotificationVisitor.h"

#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

CalibrationStatusNotification::CalibrationStatusNotification(NotificationStatus status)
    : FeederNotification(10, FeederNotificationType::CALIBRATION_STATUS_NOTIFY),
      status_(status)
{}

CalibrationStatusNotification::~CalibrationStatusNotification()
{}

vector<uint8_t> CalibrationStatusNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(status_));

    return frame;
}

void CalibrationStatusNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(status_);

    setDataSize(dataSize);
}

string CalibrationStatusNotification::getName()
{
    return string("CalibrationStatusNotification");
}

NotificationStatus CalibrationStatusNotification::getCalibrationStatus() const
{
    return status_;
}

void CalibrationStatusNotification::setCalibrationStatus(NotificationStatus status)
{
    status_ = status;
}

void CalibrationStatusNotification::accept(FeederNotificationVisitor &visitor)
{
    visitor.visit(*this);
}
