#include "HMInvalidConnectionCommandBuilder.h"
#include "HMInvalidConnectionCommand.h"

using namespace std;
using namespace communication;

unique_ptr<HMCommand> HMInvalidConnectionCommandBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto code = dataInBytes[Frame::INITIAL_DATA_POSITION];

    auto command = make_unique<HMInvalidConnectionCommand>(code);

    return move(command);
}
