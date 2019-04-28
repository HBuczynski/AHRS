#include "CalibrateMagnetometerBuilder.h"
#include "CallibrateMagnetometerCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

CalibrateMagnetometerBuilder::CalibrateMagnetometerBuilder()
{}

CalibrateMagnetometerBuilder::~CalibrateMagnetometerBuilder()
{}

unique_ptr<Command> CalibrateMagnetometerBuilder::create(const vector<uint8_t> &commandInBytes)
{
    uint8_t currentPosition = Frame::INITIAL_DATA_POSITION;
    Action status = static_cast<Action>(commandInBytes[currentPosition]);

    auto command = make_unique<CallibrateMagnetometerCommand>(status);

    return move(command);
}


