#include "CalibrateMagnetometerBuilder.h"
#include "CalibrateMgnDemandCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

CalibrateMagnetometerBuilder::CalibrateMagnetometerBuilder()
{}

CalibrateMagnetometerBuilder::~CalibrateMagnetometerBuilder()
{}

unique_ptr<FeederCommand> CalibrateMagnetometerBuilder::create(const vector<uint8_t> &commandInBytes)
{
    uint8_t currentPosition = Frame::INITIAL_DATA_POSITION;
    string planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, currentPosition);

    auto command = make_unique<CalibrateMgnDemandCommand>(planeName);

    return move(command);
}