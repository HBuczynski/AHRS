#include "ChangeFeederModeBuilder.h"
#include "ChangeFeederModeCommand.h"

using namespace std;
using namespace config;
using namespace communication;

ChangeFeederModeBuilder::ChangeFeederModeBuilder()
{}

ChangeFeederModeBuilder::~ChangeFeederModeBuilder()
{}

unique_ptr<Command> ChangeFeederModeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto  mode = static_cast<FeederMode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<ChangeFeederModeCommand>(mode);

    return move(command);
}
