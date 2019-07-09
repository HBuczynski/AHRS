#include "HMErrorCommandBuilder.h"
#include "HMErrorCommand.h"

using namespace std;
using namespace communication;

unique_ptr<HMCommand> HMErrorCommandBuilder::create(const vector<uint8_t> &dataInBytes)
{
    const auto node = static_cast<HMNodes>(dataInBytes[Frame::INITIAL_DATA_POSITION]);
    const auto error = static_cast<HMErrorType>(dataInBytes[Frame::INITIAL_DATA_POSITION + 1]);
    const auto mode = static_cast<config::UICommunicationMode>(dataInBytes[Frame::INITIAL_DATA_POSITION + 2]);

    auto command = make_unique<HMErrorCommand>(node, error, mode);

    return move(command);
}
