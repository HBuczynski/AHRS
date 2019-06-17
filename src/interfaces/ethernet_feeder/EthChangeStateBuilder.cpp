#include "EthChangeStateBuilder.h"
#include "EthChangeStateCommand.h"

using namespace std;
using namespace communication;

unique_ptr<EthFeederCommand> EthChangeStateBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto state = static_cast<FeederStateCode>(commandInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<EthChangeStateCommand>(state);

    return move(command);
}
