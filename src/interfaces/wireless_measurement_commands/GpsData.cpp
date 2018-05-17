#include "GpsData.h"
#include "MeasuringDataVisitor.h"

using namespace std;
using namespace communication;

GpsData::GpsData()
    : MeasuringData(10, MeasuringType::GPS)
{}

GpsData::~GpsData()
{}

vector<uint8_t> GpsData::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(measuringType_));

    return frame;
}

string GpsData::getName()
{
    return string("GpsData");
}

void GpsData::initializeDataSize()
{
    uint16_t dataSize = sizeof(measuringType_);
    setDataSize(dataSize);
}

void GpsData::accept(MeasuringDataVisitor &visitor)
{
    visitor.visit(*this);
}
