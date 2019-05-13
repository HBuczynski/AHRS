#include "UDPBitsNotification.h"
#include "FeederNotificationVisitor.h"

using namespace std;
using namespace communication;

UDPBitsNotification::UDPBitsNotification(BITS_ACTION code)
        : FeederNotification(10, FeederNotificationType::UDP_BITS_NOTIFY),
          code_(code)
{ }

UDPBitsNotification::~UDPBitsNotification()
{ }

vector<uint8_t> UDPBitsNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(code_));

    return frame;
}

string UDPBitsNotification::getName()
{
    return string("UDPBitsNotification");
}

void UDPBitsNotification::accept(FeederNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

BITS_ACTION UDPBitsNotification::getActionCode() const
{
    return code_;
}

void UDPBitsNotification::setActionCode(BITS_ACTION code)
{
    code = code_;
}

void UDPBitsNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(code_);

    setDataSize(dataSize);
}
