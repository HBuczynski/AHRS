#include "GUICallibrationBuilder.h"

#include "GUICallibrationCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

GUICallibrationBuilder::GUICallibrationBuilder()
{}

GUICallibrationBuilder::~GUICallibrationBuilder()
{}

unique_ptr<GUICommand> GUICallibrationBuilder::create(const vector<uint8_t> &commandInBytes)
{
    int16_t position = Frame::INITIAL_DATA_POSITION;
    const auto mode = commandInBytes[position];

    position += sizeof(mode);
    CalibrationConfiguration callibrationConfiguration;
    BytesConverter::fromVectorOfUINT8toStruct(commandInBytes, position, callibrationConfiguration);

    auto command = make_unique<GUICallibrationCommand>(callibrationConfiguration, mode);

    return move(command);
}
