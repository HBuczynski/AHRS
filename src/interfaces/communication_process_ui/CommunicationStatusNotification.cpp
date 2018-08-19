#include "CommunicationStatusNotification.h"
#include "UINotificationVisitor.h"

using namespace std;
using namespace communication;

CommunicationStatusNotification::CommunicationStatusNotification(const UIExternalStateCode &state)
    : UINotification(10, UINotificationType::COMMMUNICATION_PROCESS_STATUS),
      state_(state)
{ }

CommunicationStatusNotification::~CommunicationStatusNotification()
{ }

vector<uint8_t> CommunicationStatusNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(uiNotificationType));
    frame.push_back(static_cast<uint8_t>(state_));

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

UIExternalStateCode CommunicationStatusNotification::getState() const
{
    return state_;
}

void CommunicationStatusNotification::setState(UIExternalStateCode mode)
{
    state_ = mode;
}

void CommunicationStatusNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(uiNotificationType);
    dataSize += sizeof(state_);

    setDataSize(dataSize);
}
