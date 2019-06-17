#include "EthHandshakeBuilder.h"
#include "EthHandshakeCommand.h"

using namespace std;
using namespace communication;

unique_ptr<EthFeederCommand> EthHandshakeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<EthHandshakeCommand>();

    return move(command);
}
