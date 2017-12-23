#include "ImuData.h"

using namespace std;
using namespace communication;

ImuData::ImuData()
    : MeasuringData(10, MeasuringType::IMU)
{

}

ImuData::ImuData(const vector<uint8_t> &frameBytes)
    :MeasuringData(10, MeasuringType::IMU)
{

}

ImuData::~ImuData()
{
}

vector<uint8_t> ImuData::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t >(measuringType));



    return frame;
}

string ImuData::getName()
{
    return string("ImuData");
}
