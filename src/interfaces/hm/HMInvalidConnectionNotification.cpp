#include "HMInvalidConnectionNotification.h"
#include "HMNotificationVisitor.h"

using namespace std;
using namespace communication;

HMInvalidConnectionNotification::HMInvalidConnectionNotification(uint8_t processNumber)
        : HMNotification(10, HMNotificationType::INVALID_CONNECTION),
          processNumber_(processNumber)
{ }

HMInvalidConnectionNotification::~HMInvalidConnectionNotification()
{ }

vector<uint8_t> HMInvalidConnectionNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(processNumber_);

    return frame;
}

string HMInvalidConnectionNotification::getName()
{
    return string("HMInvalidConnectionNotification");
}

void HMInvalidConnectionNotification::accept(HMNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

void HMInvalidConnectionNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(processNumber_);

    setDataSize(dataSize);
}

uint8_t HMInvalidConnectionNotification::getProcessNumber() const
{
    return processNumber_;
}

void HMInvalidConnectionNotification::setProcessNumber(const uint8_t &processNumber)
{
    processNumber_ = processNumber;
}

