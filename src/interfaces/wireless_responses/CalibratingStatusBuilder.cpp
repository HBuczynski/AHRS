#include "CalibratingStatusBuilder.h"
#include "CalibratingStatusResponse.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

CalibratingStatusBuilder::CalibratingStatusBuilder()
{}

CalibratingStatusBuilder::~CalibratingStatusBuilder()
{}

unique_ptr<Response> CalibratingStatusBuilder::create(const vector<uint8_t> &dataInBytes)
{
    int16_t position = Frame::INITIAL_DATA_POSITION;
    const auto mode = dataInBytes[position];

    position += sizeof(mode);
    CalibrationConfiguration callibrationConfiguration;
    BytesConverter::fromVectorOfUINT8toStruct(dataInBytes, position, callibrationConfiguration);

    auto command = make_unique<CalibratingStatusResponse>(callibrationConfiguration, mode);

    return move(command);
}
