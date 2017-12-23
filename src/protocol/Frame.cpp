#include "Frame.h"

using namespace std;
using namespace communication;

Frame::Frame(FrameType frameTypeIn, uint8_t dataSizeIn)
    : systemVersion(1),
      frameType(frameTypeIn),
      packetNumber(0),
      dataSize(dataSizeIn)
{
}

Frame::~Frame()
{
}

vector<uint8_t> Frame::getHeader()
{
    vector<uint8_t > header;
    header.push_back(systemVersion);
    header.push_back(static_cast<uint8_t >(frameType));
    header.push_back(packetNumber);
    header.push_back(dataSize);

    return header;
}

const uint8_t& Frame::getPacketNumber()
{
    return packetNumber;
}

void Frame::setPacketNumber(uint8_t number)
{
    packetNumber = number;
}

const uint8_t& Frame::getSystemVersion()
{
    return systemVersion;
}

const uint8_t& Frame::getDataSize()
{
    return dataSize;
}

const FrameType &Frame::getFrameType()
{
    return frameType;
}
