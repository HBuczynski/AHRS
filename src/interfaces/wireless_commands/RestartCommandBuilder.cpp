#include "RestartCommandBuilder.h"
#include "RestartCommand.h"

using namespace std;
using namespace communication;

RestartCommandBuilder::RestartCommandBuilder()
{}

RestartCommandBuilder::~RestartCommandBuilder()
{}

unique_ptr<Command> RestartCommandBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<RestartCommand>();

    return move(command);
}
