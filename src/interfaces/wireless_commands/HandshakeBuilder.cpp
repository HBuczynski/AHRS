#include "HandshakeBuilder.h"
#include "HandshakeCommand.h"

using namespace std;
using namespace config;
using namespace communication;

HandshakeBuilder::HandshakeBuilder()
{}

HandshakeBuilder::~HandshakeBuilder()
{}

unique_ptr<Command> HandshakeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto  mode = static_cast<FeederMode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<HandshakeCommand>(mode);

    return move(command);
}

