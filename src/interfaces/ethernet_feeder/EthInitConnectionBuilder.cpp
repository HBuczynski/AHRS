#include "EthInitConnectionBuilder.h"
#include "EthInitConnectionCommand.h"

using namespace std;
using namespace communication;

unique_ptr<EthFeederCommand> EthInitConnectionBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<EthInitConnectionCommand>();

    return move(command);
}
