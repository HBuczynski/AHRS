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
    string planeName;

    planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, INIT_DATA_POSITION_IN_FRAME);

    auto command = make_unique<CallibrateMagnetometerCommand>(planeName);

    return move(command);
}


