#include "FeederNotificationFactory.h"
#include "CalibrationStatusNotificationBuilder.h"

using namespace std;
using namespace communication;

FeederNotificationFactory::FeederNotificationFactory()
{}

FeederNotificationFactory::~FeederNotificationFactory()
{}

unique_ptr<FeederNotification> FeederNotificationFactory::createNotification(const std::vector<uint8_t> &notificationInBytes)
{
    const auto type = static_cast<FeederNotificationType >(notificationInBytes[Notification_TYPE_POSITION]);

    switch (type)
    {
        case FeederNotificationType::CALIBRATION_STATUS:
            builder_ = make_unique<CalibrationStatusNotificationBuilder>();
            return move(builder_->create(notificationInBytes));
        default:
            throw invalid_argument("Received Notification does not register in factory.");

    }
}