#include "CommunicationStatusNotification.h"
#include "UINotificationVisitor.h"

using namespace std;
using namespace communication;

CommunicationStatusNotification::CommunicationStatusNotification(const UIExternalComCode &state, config::UICommunicationMode mode)
    : UINotification(10, UINotificationType::COMMMUNICATION_PROCESS_STATUS),
      state_(state),
      mode_(mode)
{ }

CommunicationStatusNotification::~CommunicationStatusNotification()
{ }

vector<uint8_t> CommunicationStatusNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(uiNotificationType));
    frame.push_back(static_cast<uint8_t>(state_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string CommunicationStatusNotification::getName()
{
    return string("CommunicationStatusNotification");
}

void CommunicationStatusNotification::accept(UINotificationVisitor &visitor)
{
    visitor.visit(*this);
}

UIExternalComCode CommunicationStatusNotification::getState() const
{
    return state_;
}

void CommunicationStatusNotification::setState(UIExternalComCode mode)
{
    state_ = mode;
}

config::UICommunicationMode CommunicationStatusNotification::getUIMode() const
{
    return mode_;
}

void CommunicationStatusNotification::setUIMode(config::UICommunicationMode mode)
{
    mode_ = mode;
}

void CommunicationStatusNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(uiNotificationType);
    dataSize += sizeof(state_);
    dataSize += sizeof(mode_);

    setDataSize(dataSize);
}
