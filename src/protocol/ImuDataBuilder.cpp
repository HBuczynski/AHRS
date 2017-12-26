#include "ImuDataBuilder.h"
#include "ImuData.h"

using namespace std;
using namespace communication;

ImuDataBuilder::ImuDataBuilder()
{}

unique_ptr<MeasuringData> ImuDataBuilder::create(const vector<uint8_t> &dataInBytes)
{
    auto command = make_unique<ImuData>();

    return move(command);
}
