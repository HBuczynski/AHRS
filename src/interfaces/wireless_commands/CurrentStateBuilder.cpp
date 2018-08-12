#include "CurrentStateBuilder.h"
#include "CurrentStateCommand.h"

using namespace std;
using namespace communication;


CurrentStateBuilder::CurrentStateBuilder()
{}

CurrentStateBuilder::~CurrentStateBuilder()
{}

unique_ptr<Command> CurrentStateBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<CurrentStateCommand>();

    return move(command);
}
