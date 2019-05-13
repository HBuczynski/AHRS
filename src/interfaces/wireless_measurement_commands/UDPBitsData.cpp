#include "UDPBitsData.h"
#include "MeasuringDataVisitor.h"

using namespace std;
using namespace communication;

UDPBitsData::UDPBitsData()
    : MeasuringData(10, MeasuringType::UDP_BITS_DATA)
{}

UDPBitsData::~UDPBitsData()
{}

vector<uint8_t> UDPBitsData::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(measuringType_));

    return frame;
}

string UDPBitsData::getName()
{
    return string("UDPBitsData");
}

void UDPBitsData::initializeDataSize()
{
    uint16_t dataSize = sizeof(measuringType_);

    setDataSize(dataSize);
}

void UDPBitsData::accept(MeasuringDataVisitor &visitor)
{
    visitor.visit(*this);
}
