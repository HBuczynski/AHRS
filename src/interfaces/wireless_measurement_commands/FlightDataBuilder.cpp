#include "FlightDataBuilder.h"
#include "FlightData.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

FlightDataBuilder::FlightDataBuilder()
{}

unique_ptr<MeasuringData> FlightDataBuilder::create(const vector<uint8_t> &dataInBytes)
{
    uint16_t dataSize = BytesConverter::fromVectorOfUINT8toUINT16(dataInBytes, Frame::DATA_SIZE_UINT16_POSITION) - 1;

    if((dataSize % sizeof(FlightMeasurements)) != 0)
    {
        throw invalid_argument("FlightDataBuilder: wrong data in command");
    }
    uint16_t currentPosition = Frame::INITIAL_DATA_POSITION;

    FlightMeasurements measurements;
    BytesConverter::fromVectorOfUINT8toStruct(dataInBytes, currentPosition, measurements);

    auto command = make_unique<FlightData>(measurements);
    return move(command);
}
