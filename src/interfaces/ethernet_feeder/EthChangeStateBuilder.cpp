#include "EthChangeStateBuilder.h"
#include "EthChangeStateCommand.h"

using namespace std;
using namespace communication;

unique_ptr<EthFeederCommand> EthChangeStateBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<EthChangeStateCommand>();

    return move(command);
}
