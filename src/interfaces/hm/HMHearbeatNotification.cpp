#include "HMHeartbeatNotification.h"
#include "HMNotificationVisitor.h"

using namespace std;
using namespace communication;

HMHeartbeatNotification::HMHeartbeatNotification(HMNodes code)
        : HMNotification(10, HMNotificationType::HEARTBEAT),
          code_(code)
{ }

HMHeartbeatNotification::~HMHeartbeatNotification()
{ }

vector<uint8_t> HMHeartbeatNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string HMHeartbeatNotification::getName()
{
    return string("HMHeartbeatNotification");
}

void HMHeartbeatNotification::accept(HMNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

HMNodes HMHeartbeatNotification::getHMNode() const
{
    return code_;
}

void HMHeartbeatNotification::setHMNode(HMNodes code)
{
    code = code_;
}

void HMHeartbeatNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
