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
    PlaneStatus status = static_cast<PlaneStatus>(commandInBytes[currentPosition]);

    currentPosition += sizeof(status);
    string planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, currentPosition);


    auto command = make_unique<CallibrateMagnetometerCommand>(planeName, status);

    return move(command);
}


