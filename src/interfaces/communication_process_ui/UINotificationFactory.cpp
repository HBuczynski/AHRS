#include "UINotificationFactory.h"

#include "CommunicationStatusBuilder.h"
#include "ReceivingDataBuilder.h"

using namespace std;
using namespace communication;

UINotificationFactory::UINotificationFactory()
{ }

UINotificationFactory::~UINotificationFactory()
{ }

unique_ptr<UINotification> UINotificationFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<UINotificationType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case UINotificationType ::COMMMUNICATION_PROCESS_STATUS :
            builder_ = make_unique<CommunicationStatusBuilder>();
            return move(builder_->create(commandInBytes));
        case UINotificationType ::RECEIVING_DATA :
            builder_ = make_unique<ReceivingDataBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
