#include "UDPBitsDataBuilder.h"
#include "UDPBitsData.h"

using namespace std;
using namespace communication;

UDPBitsDataBuilder::UDPBitsDataBuilder()
{}

unique_ptr<MeasuringData> UDPBitsDataBuilder::create(const vector<uint8_t> &dataInBytes)
{
    auto command = make_unique<UDPBitsData>();

    return move(command);
}
