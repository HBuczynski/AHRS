#include "ImuDataBuilder.h"

using namespace std;
using namespace communication;

ImuDataBuilder::ImuDataBuilder()
{}

unique_ptr<MeasuringData> ImuDataBuilder::create(const vector<uint8_t> &dataInBytes)
{
    return unique_ptr<MeasuringData>();
}
