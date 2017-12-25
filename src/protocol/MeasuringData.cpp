#include "MeasuringData.h"

using namespace std;
using namespace communication;

MeasuringData::MeasuringData(uint8_t dataSizeIn, MeasuringType measuringTypeIn)
    : Frame(FrameType::RESPONSE, dataSizeIn),
      measuringType_(measuringTypeIn)
{
}

MeasuringData::~MeasuringData()
{
}

const MeasuringType &MeasuringData::getMeasuringType() const
{
    return measuringType_;
}
