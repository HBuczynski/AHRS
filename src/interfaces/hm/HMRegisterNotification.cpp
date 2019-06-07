#include "HMRegisterNotification.h"
#include "HMNotificationVisitor.h"

using namespace std;
using namespace communication;

HMRegisterNotification::HMRegisterNotification(HMNodes code)
        : HMNotification(10, HMNotificationType::HEARTBEAT),
          code_(code)
{ }

HMRegisterNotification::~HMRegisterNotification()
{ }

vector<uint8_t> HMRegisterNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string HMRegisterNotification::getName()
{
    return string("HMRegisterNotification");
}

void HMRegisterNotification::accept(HMNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

HMNodes HMRegisterNotification::getHMNode() const
{
    return code_;
}

void HMRegisterNotification::setHMNode(HMNodes code)
{
    code = code_;
}

void HMRegisterNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
