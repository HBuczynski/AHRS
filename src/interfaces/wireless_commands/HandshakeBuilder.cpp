#include "HandshakeBuilder.h"
#include "HandshakeCommand.h"

using namespace std;
using namespace communication;

HandshakeBuilder::HandshakeBuilder()
{}

HandshakeBuilder::~HandshakeBuilder()
{}

unique_ptr<Command> HandshakeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<HandshakeCommand>();

    return move(command);
}

