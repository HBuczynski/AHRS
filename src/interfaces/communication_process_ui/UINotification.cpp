#include "UINotification.h"

using namespace std;
using namespace communication;

UINotification::UINotification(uint8_t dataSizeIn, UINotificationType commandTypeIn)
        : Frame(FrameType::NOTIFICATION, InterfaceType::COMMUNICATION_PROCESS_UI, dataSizeIn),
          uiNotificationType(commandTypeIn)
{}

UINotification::~UINotification()
{}

const UINotificationType &UINotification::getCommandType() const
{
    return uiNotificationType;
}