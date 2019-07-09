#include "FMResetCommunicationProcessBuilder.h"
#include "FMResetCommunicationProcessCommand.h"

using namespace std;
using namespace communication;

unique_ptr<FMCommand> FMResetCommunicationProcessBuilder::create(const std::vector<uint8_t> &dataInBytes)
{
    const auto mode = static_cast<config::UICommunicationMode>(dataInBytes[Frame::INITIAL_DATA_POSITION]);
    auto command = make_unique<FMResetCommunicationProcessCommand>(mode);

    return move(command);
}

