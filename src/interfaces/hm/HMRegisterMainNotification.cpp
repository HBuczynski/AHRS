#include "HMRegisterMainNotification.h"
#include "HMNotificationVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

HMRegisterMainNotification::HMRegisterMainNotification(HMNodes code, const string& queueName, uint32_t size)
        : HMNotification(10, HMNotificationType::MAIN_REGISTER),
          code_(code),
          queueName_(queueName),
          size_(size)
{ }

HMRegisterMainNotification::~HMRegisterMainNotification()
{ }

vector<uint8_t> HMRegisterMainNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(notificationType_));
    frame.push_back(static_cast<uint8_t>(code_));

    BytesConverter::appendStringToVectorOfUINT8(queueName_, frame);
    BytesConverter::appendUINT32toVectorOfUINT8(size_, frame);

    return frame;
}

string HMRegisterMainNotification::getName()
{
    return string("HMRegisterMainNotification");
}

void HMRegisterMainNotification::accept(HMNotificationVisitor &visitor)
{
    visitor.visit(*this);
}

HMNodes HMRegisterMainNotification::getHMNode() const
{
    return code_;
}

void HMRegisterMainNotification::setHMNode(HMNodes code)
{
    code = code_;
}

const std::string& HMRegisterMainNotification::getQueueName() const noexcept
{
    return queueName_;
}

void HMRegisterMainNotification::setQueueName(const std::string& queueName)
{
    queueName_ = queueName;
}

uint32_t HMRegisterMainNotification::getSize() const noexcept
{
    return size_;
}

void HMRegisterMainNotification::setSize(uint32_t size)
{
    size_ = size;
}

void HMRegisterMainNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(notificationType_);

    dataSize += sizeof(code_);
    dataSize += queueName_.size() + sizeof(END_STRING_IN_FRAME);
    dataSize += sizeof(size_);

    setDataSize(dataSize);
}
