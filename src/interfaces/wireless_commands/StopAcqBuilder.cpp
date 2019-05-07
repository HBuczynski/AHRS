#include "StopAcqBuilder.h"
#include "StopAcqCommand.h"

using namespace std;
using namespace communication;

StopAcqBuilder::StopAcqBuilder()
{}

StopAcqBuilder::~StopAcqBuilder()
{}

unique_ptr<Command> StopAcqBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<StopAcqCommand>();

    return move(command);
}

