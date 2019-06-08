#include "HMErrorNotification.h"
#include "HMNotificationVisitor.h"

using namespace std;
using namespace communication;

HMErrorNotification::HMErrorNotification(HMNodes node, HMErrorType error)
        : HMNotification(10, HMNotificationType::ERROR),
          node_(node),
          error_(error)
{ }

HMErrorNotification::~HMErrorNotification()
{ }

vector<uint8_t> HMErrorNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(node_));
    frame.push_back(static_cast<uint8_t>(error_));

    return frame;
}

string HMErrorNotification::getName()
{
    return string("HMErrorNotification");
}

void HMErrorNotification::accept(HMNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

HMNodes HMErrorNotification::getHMNode() const
{
    return node_;
}

void HMErrorNotification::setHMNode(HMNodes node)
{
    node_ = node;
}


HMErrorType HMErrorNotification::getHMError() const
{
    return error_;
}

void HMErrorNotification::setHMError(HMErrorType error)
{
    error_ = error;
}

void HMErrorNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(error_);
    dataSize += sizeof(node_);

    setDataSize(dataSize);
}
