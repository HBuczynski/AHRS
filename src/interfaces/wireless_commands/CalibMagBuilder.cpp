#include "CalibMagBuilder.h"
#include "CallibrateMagnetometerCommand.h"

using namespace std;
using namespace communication;

CalibMagBuilder::CalibMagBuilder()
{}

CalibMagBuilder::~CalibMagBuilder()
{}

unique_ptr<Command> CalibMagBuilder::create(const vector<uint8_t> &commandInBytes)
{
    Action action = static_cast<Action>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<CallibrateMagnetometerCommand>(action);

    return move(command);
}
