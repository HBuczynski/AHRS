#include "FMChangeChannelBuilder.h"
#include "FMChangeChannelCommand.h"

using namespace std;
using namespace communication;

unique_ptr<FMCommand> FMChangeChannelBuilder::create(const std::vector<uint8_t> &dataInBytes)
{
    const auto mode = dataInBytes[Frame::INITIAL_DATA_POSITION];
    auto command = make_unique<FMChangeChannelCommand>(mode);

    return move(command);
}

