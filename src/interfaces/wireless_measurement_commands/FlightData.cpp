#include "FlightData.h"
#include "MeasuringDataVisitor.h"

#include <BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

FlightData::FlightData(FlightMeasurements measurements)
        : MeasuringData(10, MeasuringType::FLIGHT_DATA),
          measurements_(measurements)
{}

FlightData::~FlightData()
{}

vector<uint8_t> FlightData::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(measuringType_));

    const auto serializedMeasurements = BytesConverter::appendStructToVectorOfUINT8(measurements_);
    frame.insert(frame.end(), serializedMeasurements.begin(), serializedMeasurements.end());

    return frame;
}

string FlightData::getName()
{
    return string("FlightData");
}

void FlightData::accept(MeasuringDataVisitor &visitor)
{
    visitor.visit(*this);
}

FlightMeasurements FlightData::getMeasurements() const
{
    return measurements_;
}

void FlightData::setMeasurements(FlightMeasurements measurements)
{
    measurements_ = measurements;
}

void FlightData::initializeDataSize()
{
    dataSize_ = sizeof(measuringType_);
    dataSize_ += sizeof(measurements_);
}
