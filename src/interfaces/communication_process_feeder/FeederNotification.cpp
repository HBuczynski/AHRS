#include "FeederNotification.h"

using namespace std;
using namespace communication;

FeederNotification::FeederNotification(uint8_t dataSizeIn, FeederNotificationType NotificationTypeIn)
        : Frame(FrameType::NOTIFICATION, InterfaceType::COMMUNICATION_PROCESS_FEEDER, dataSizeIn),
          notificationType_(NotificationTypeIn)
{}

FeederNotification::~FeederNotification()
{}

const FeederNotificationType &FeederNotification::getNotificationType() const
{
    return notificationType_;
}
