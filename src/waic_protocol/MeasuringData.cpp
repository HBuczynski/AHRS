#include "MeasuringData.h"

using namespace std;
using namespace communication;

MeasuringData::MeasuringData(uint8_t dataSizeIn, MeasuringType measuringTypeIn)
    : Frame(FrameType::RESPONSE, dataSizeIn),
      measuringType(measuringTypeIn)
{
}

MeasuringData::~MeasuringData()
{
}

const MeasuringType &MeasuringData::getMeasuringType()
{
    return measuringType;
}
