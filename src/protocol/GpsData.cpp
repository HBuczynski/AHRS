#include "GpsData.h"

using namespace std;
using namespace communication;

GpsData::GpsData()
    : MeasuringData(10, MeasuringType::GPS)
{}

GpsData::~GpsData()
{}

vector<uint8_t> GpsData::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(measuringType_));

    return frame;
}

string GpsData::getName()
{
    return string("GpsData");
}
