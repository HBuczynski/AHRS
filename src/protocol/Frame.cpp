#include "Frame.h"

using namespace std;
using namespace communication;

Frame::Frame(FrameType frameTypeIn, uint8_t dataSizeIn)
    : systemVersion_(1),
      frameType_(frameTypeIn),
      packetNumber_(0),
      dataSize_(dataSizeIn)
{
}

Frame::~Frame()
{
}

vector<uint8_t> Frame::getHeader() const
{
    vector<uint8_t > header;
    header.push_back(systemVersion_);
    header.push_back(static_cast<uint8_t >(frameType_));
    header.push_back(packetNumber_);
    header.push_back(dataSize_);

    return header;
}

const uint8_t& Frame::getPacketNumber() const
{
    return packetNumber_;
}

void Frame::setPacketNumber(uint8_t number)
{
    packetNumber_ = number;
}

const uint8_t& Frame::getSystemVersion() const
{
    return systemVersion_;
}

const uint8_t& Frame::getDataSize() const
{
    return dataSize_;
}

void Frame::setDataSize(uint8_t dataSize)
{
    dataSize_ = dataSize;
}

const FrameType &Frame::getFrameType() const
{
    return frameType_;
}
