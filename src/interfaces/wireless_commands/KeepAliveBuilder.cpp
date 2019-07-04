#include "KeepAliveBuilder.h"
#include "KeepAliveCommand.h"

using namespace std;
using namespace communication;

KeepAliveBuilder::KeepAliveBuilder()
{}

KeepAliveBuilder::~KeepAliveBuilder()
{}

unique_ptr<Command> KeepAliveBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<KeepAliveCommand>();

    return move(command);
}

