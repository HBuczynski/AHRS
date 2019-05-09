#include "DbHashNotification.h"
#include "FeederNotificationVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

DbHashNotification::DbHashNotification(uint32_t hash)
        : FeederNotification(10, FeederNotificationType::DB_HASH),
          hash_(hash)
{ }

DbHashNotification::~DbHashNotification()
{ }

vector<uint8_t> DbHashNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    BytesConverter::appendUINT32toVectorOfUINT8(hash_, frame);

    return frame;
}

string DbHashNotification::getName()
{
    return string("DbHashNotification");
}

void DbHashNotification::accept(FeederNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

uint32_t DbHashNotification::getHash() const noexcept
{
    return hash_;
}

void DbHashNotification::setHash(uint32_t hash) noexcept
{
    hash = hash_;
}

void DbHashNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);
    dataSize += sizeof(hash_);

    setDataSize(dataSize);
}
