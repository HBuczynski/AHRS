#include "HMRemoveNodeNotification.h"
#include "HMNotificationVisitor.h"

using namespace std;
using namespace communication;

HMRemoveNodeNotification::HMRemoveNodeNotification(HMNodes code)
        : HMNotification(10, HMNotificationType::REMOVE_NODE),
          code_(code)
{ }

HMRemoveNodeNotification::~HMRemoveNodeNotification()
{ }

vector<uint8_t> HMRemoveNodeNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string HMRemoveNodeNotification::getName()
{
    return string("HMRemoveNodeNotification");
}

void HMRemoveNodeNotification::accept(HMNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

HMNodes HMRemoveNodeNotification::getHMNode() const
{
    return code_;
}

void HMRemoveNodeNotification::setHMNode(HMNodes code)
{
    code = code_;
}

void HMRemoveNodeNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
