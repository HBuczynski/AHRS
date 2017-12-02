#include "WAICMeasuringData.h"

using namespace std;
using namespace communication;

WAICMeasuringData::WAICMeasuringData(uint8_t dataSizeIn, WAICMeasuringType measuringTypeIn)
    : WAICFrame(WAICFrameType::RESPONSE, dataSizeIn),
      measuringType(measuringTypeIn)
{
}

WAICMeasuringData::~WAICMeasuringData()
{
}

const WAICMeasuringType &WAICMeasuringData::getMeasuringType()
{
    return measuringType;
}
