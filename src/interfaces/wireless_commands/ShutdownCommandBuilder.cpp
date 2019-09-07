#include "ShutdownCommandBuilder.h"
#include "ShutdownCommand.h"

using namespace std;
using namespace communication;

ShutdownCommandBuilder::ShutdownCommandBuilder()
{}

ShutdownCommandBuilder::~ShutdownCommandBuilder()
{}

unique_ptr<Command> ShutdownCommandBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<ShutdownCommand>();

    return move(command);
}
