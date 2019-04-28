#include "CalibrateAccelerometerBuilder.h"

#include "CalibrateAccelerometerCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

CalibrateAccelerometerBuilder::CalibrateAccelerometerBuilder()
{}

CalibrateAccelerometerBuilder::~CalibrateAccelerometerBuilder()
{}

unique_ptr<Command> CalibrateAccelerometerBuilder::create(const vector<uint8_t> &commandInBytes)
{
    uint8_t currentPosition = Frame::INITIAL_DATA_POSITION;
    const uint8_t axis = commandInBytes[currentPosition];
    currentPosition++;

    const auto action = static_cast<AccelAction>(commandInBytes[currentPosition]);
    auto command = make_unique<CalibrateAccelerometerCommand>(axis, action);

    return move(command);
}
