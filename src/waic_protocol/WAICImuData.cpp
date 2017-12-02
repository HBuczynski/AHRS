#include "WAICImuData.h"

using namespace std;
using namespace communication;

WAICImuData::WAICImuData()
    : WAICMeasuringData(10, WAICMeasuringType::IMU)
{

}

WAICImuData::WAICImuData(const vector<uint8_t> &frameBytes)
    :WAICMeasuringData(10, WAICMeasuringType::IMU)
{

}

WAICImuData::~WAICImuData()
{
}

vector<uint8_t> WAICImuData::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(measuringType));



    return frame;
}

string WAICImuData::getName()
{
    return string("ImuData");
}
