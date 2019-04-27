#include "StateNotification.h"
#include "FeederNotificationVisitor.h"

using namespace std;
using namespace communication;

StateNotification::StateNotification(FeederStateCode code)
        : FeederNotification(10, FeederNotificationType::STATE),
          code_(code)
{ }

StateNotification::~StateNotification()
{ }

vector<uint8_t> StateNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string StateNotification::getName()
{
    return string("StateNotification");
}

void StateNotification::accept(FeederNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

FeederStateCode StateNotification::getStateCode() const
{
    return code_;
}

void StateNotification::setAckType(FeederStateCode code)
{
    code = code_;
}

void StateNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
