#include "ImuData.h"
#include "MeasuringDataVisitor.h"

using namespace std;
using namespace communication;

ImuData::ImuData()
    : MeasuringData(10, MeasuringType::IMU)
{}


ImuData::~ImuData()
{}

vector<uint8_t> ImuData::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(measuringType_));

    return frame;
}

string ImuData::getName()
{
    return string("ImuData");
}

void ImuData::initializeDataSize()
{
    uint16_t dataSize = sizeof(measuringType_);

    setDataSize(dataSize);
}

void ImuData::accept(MeasuringDataVisitor &visitor)
{
    visitor.visit(*this);
}
