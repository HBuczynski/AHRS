#include "SetPlaneMagnetometerBuilder.h"
#include "SetPlaneMagnetometerCommand.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

SetPlaneMagnetometerBuilder::SetPlaneMagnetometerBuilder()
{}

SetPlaneMagnetometerBuilder::~SetPlaneMagnetometerBuilder()
{}

unique_ptr<Command> SetPlaneMagnetometerBuilder::create(const vector<uint8_t> &commandInBytes)
{
    string planeName;

    planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, INIT_DATA_POSITION_IN_FRAME);

    auto command = make_unique<SetPlaneMagnetometerCommand>(planeName);

    return move(command);
}


