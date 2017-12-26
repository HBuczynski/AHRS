#include "GpsDataBuilder.h"
#include "GpsData.h"

using namespace std;
using namespace communication;

GpsDataBuilder::GpsDataBuilder()
{}

unique_ptr<MeasuringData> GpsDataBuilder::create(const vector<uint8_t> &dataInBytes)
{
    auto command = make_unique<GpsData>();

    return move(command);
}
