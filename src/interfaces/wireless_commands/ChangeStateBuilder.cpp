#include "ChangeStateBuilder.h"
#include "ChangeStateCommand.h"

using namespace std;
using namespace communication;

ChangeStateBuilder::ChangeStateBuilder()
{}

ChangeStateBuilder::~ChangeStateBuilder()
{}

unique_ptr<Command> ChangeStateBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<ChangeStateCommand>(static_cast<FeederStateCode>(commandInBytes[Frame::INITIAL_DATA_POSITION]));
    return move(command);
}

