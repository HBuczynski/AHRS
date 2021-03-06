#include "ReceivingDataNotification.h"
#include "UINotificationVisitor.h"

using namespace std;
using namespace communication;

ReceivingDataNotification::ReceivingDataNotification(uint8_t communicationMode, const vector<uint8_t> &data)
    : UINotification(10, UINotificationType::RECEIVING_DATA),
      communicationMode_(communicationMode),
      data_(data)
{ }

ReceivingDataNotification::~ReceivingDataNotification()
{ }

vector<uint8_t> ReceivingDataNotification::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(uiNotificationType));

    frame.push_back(communicationMode_);
    frame.insert(frame.end(), data_.begin(), data_.end());

    return frame;
}

string ReceivingDataNotification::getName()
{
    return string("ReceivingDataNotification");
}

void ReceivingDataNotification::accept(UINotificationVisitor &visitor)
{
    visitor.visit(*this);
}

const vector<uint8_t> &ReceivingDataNotification::getData() const
{
    return data_;
}

void ReceivingDataNotification::setData(const vector<uint8_t> &data)
{
    data_ = data;
}

void ReceivingDataNotification::initializeDataSize()
{
    uint16_t dataSize = sizeof(uiNotificationType);
    dataSize += data_.size();
    dataSize += sizeof(communicationMode_);

    setDataSize(dataSize);
}

uint8_t ReceivingDataNotification::getCommunicationMode() const
{
    return communicationMode_;
}

void ReceivingDataNotification::setCommunicationMode(const uint8_t &communicationMode)
{
    communicationMode_ = communicationMode;
}
