#include "EthHandshakeBuilder.h"
#include "EthHandshakeCommand.h"

using namespace std;
using namespace communication;

unique_ptr<EthFeederCommand> EthHandshakeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto mode = static_cast<config::FeederMode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);

    auto command = make_unique<EthHandshakeCommand>(mode);

    return move(command);
}
