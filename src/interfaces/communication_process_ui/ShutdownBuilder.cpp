#include "ShutdownBuilder.h"
#include "ShutdownCommand.h"

using namespace std;
using namespace communication;

ShutdownBuilder::ShutdownBuilder()
{}

ShutdownBuilder::~ShutdownBuilder()
{}

unique_ptr<UICommand> ShutdownBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<ShutdownCommand>();

    return move(command);
}
