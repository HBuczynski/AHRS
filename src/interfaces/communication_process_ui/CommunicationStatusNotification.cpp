#include "CommunicationStatusNotification.h"
#include "UINotificationVisitor.h"

using namespace std;
using namespace communication;

CommunicationStatusNotification::CommunicationStatusNotification(const UIExternalComCode &state, uint8_t processNumber)
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

UIExternalComCode CommunicationStatusNotification::getState() const
{
    return state_;
}

void CommunicationStatusNotification::setState(UIExternalComCode mode)
{
    state_ = mode;
}

uint8_t CommunicationStatusNotification::getProcessNumber() const
{
    return processNumber_;
}

void CommunicationStatusNotification::setProcessNumber(uint8_t processNumber)
{
    processNumber_ = processNumber;
}

void CommunicationStatusNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(uiNotificationType);
    dataSize += sizeof(state_);

    setDataSize(dataSize);
}