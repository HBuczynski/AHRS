#include "ImuData.h"
#include "MeasuringDataVisitor.h"

using namespace std;
using namespace communication;

ImuData::ImuData(uint8_t measurement)
    : MeasuringData(10, MeasuringType::IMU),
      measurement_(measurement)
{}


ImuData::~ImuData()
{}

vector<uint8_t> ImuData::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(measuringType_));

    return frame;
}

uint8_t ImuData::getMeasurement() const
{
    return measurement_;
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
