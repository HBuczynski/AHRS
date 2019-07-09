#include "HMNotificationFactory.h"

#include "HMRegisterBuilder.h"
#include "HMHeartbeatBuilder.h"
#include "HMRegisterMainBuilder.h"
#include "HMErrorBuilder.h"
#include "HMRemoveNodeBuilder.h"

#include <iostream>

using namespace std;
using namespace communication;

HMNotificationFactory::HMNotificationFactory()
{}

HMNotificationFactory::~HMNotificationFactory()
{}

unique_ptr<HMNotification> HMNotificationFactory::createNotification(const std::vector<uint8_t> &notificationInBytes)
{
    const auto type = static_cast<HMNotificationType >(notificationInBytes[Frame::NOTIFICATION_TYPE_POSITION]);

    switch (type)
    {
        case HMNotificationType::REGISTER:
            builder_ = make_unique<HMRegisterBuilder>();
            return move(builder_->create(notificationInBytes));

        case HMNotificationType::HEARTBEAT:
            builder_ = make_unique<HMHeartbeatBuilder>();
            return move(builder_->create(notificationInBytes));

        case HMNotificationType::MAIN_REGISTER:
            builder_ = make_unique<HMRegisterMainBuilder>();
            return move(builder_->create(notificationInBytes));

        case HMNotificationType::ERROR:
            builder_ = make_unique<HMErrorBuilder>();
            return move(builder_->create(notificationInBytes));

        case HMNotificationType::REMOVE_NODE:
            builder_ = make_unique<HMRemoveNodeBuilder>();
            return move(builder_->create(notificationInBytes));

        default:
            throw invalid_argument("Received HM notification does not register in factory.");

    }
}
