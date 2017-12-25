#include "GpsDataBuilder.h"

using namespace std;
using namespace communication;

GpsDataBuilder::GpsDataBuilder()
{

}

unique_ptr<MeasuringData> GpsDataBuilder::create(const vector<uint8_t> &dataInBytes)
{
    return unique_ptr<MeasuringData>();
}
