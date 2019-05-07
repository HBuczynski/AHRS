#include "FeederData.h"
#include "MeasuringDataVisitor.h"

#include <BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

FeederData::FeederData(FeederGeneralData measurements)
        : MeasuringData(10, MeasuringType::FLIGHT_DATA),
          measurements_(measurements)
{}

FeederData::~FeederData()
{}

vector<uint8_t> FeederData::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(measuringType_));

    const auto serializedMeasurements = BytesConverter::appendStructToVectorOfUINT8(measurements_);
    frame.insert(frame.end(), serializedMeasurements.begin(), serializedMeasurements.end());

    return frame;
}

string FeederData::getName()
{
    return string("FlightData");
}

void FeederData::accept(MeasuringDataVisitor &visitor)
{
    visitor.visit(*this);
}

FeederGeneralData FeederData::getMeasurements() const
{
    return measurements_;
}

void FeederData::setMeasurements(FeederGeneralData measurements)
{
    measurements_ = measurements;
}

void FeederData::initializeDataSize()
{
    dataSize_ = sizeof(measuringType_);
    dataSize_ += sizeof(measurements_);
}
