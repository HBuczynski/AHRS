#include "BITSDataBuilder.h"
#include "BITSDataCommand.h"

using namespace std;
using namespace communication;

BITSDataBuilder::BITSDataBuilder()
{}

BITSDataBuilder::~BITSDataBuilder()
{}

unique_ptr<Command> BITSDataBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<BITSDataCommand>();

    return move(command);
}
