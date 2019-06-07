#include "HMNotification.h"

using namespace std;
using namespace communication;

HMNotification::HMNotification(uint8_t dataSizeIn, HMNotificationType notificationTypeIn)
        : Frame(FrameType::NOTIFICATION, InterfaceType::HM, dataSizeIn),
          notificationType_(notificationTypeIn)
{}

HMNotification::~HMNotification()
{}

const HMNotificationType &HMNotification::getNotificationType() const
{
    return notificationType_;
}
