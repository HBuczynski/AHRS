#include "WAICFrame.h"

using namespace std;
using namespace communication;

WAICFrame::WAICFrame(WAICFrameType frameTypeIn, uint8_t dataSizeIn)
    : systemVersion(1),
      frameType(frameTypeIn),
      packetNumber(0),
      dataSize(dataSizeIn)
{
}

WAICFrame::~WAICFrame()
{
}

vector<uint8_t> WAICFrame::getHeader()
{
    vector<uint8_t > header;
    header.push_back(systemVersion);
    header.push_back(static_cast<uint8_t >(frameType));
    header.push_back(packetNumber);
    header.push_back(dataSize);

    return header;
}

const uint8_t& WAICFrame::getPacketNumber()
{
    return packetNumber;
}

void WAICFrame::setPacketNumber(uint8_t number)
{
    packetNumber = number;
}

const uint8_t& WAICFrame::getSystemVersion()
{
    return systemVersion;
}

const uint8_t& WAICFrame::getDataSize()
{
    return dataSize;
}

const WAICFrameType &WAICFrame::getFrameType()
{
    return frameType;
}
