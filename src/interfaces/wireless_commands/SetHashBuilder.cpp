#include "SetHashBuilder.h"
#include "SetHashCommand.h"

#include <utility/BytesConverter.h>
#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

SetHashBuilder::SetHashBuilder()
{}

SetHashBuilder::~SetHashBuilder()
{}

unique_ptr<Command> SetHashBuilder::create(const vector<uint8_t> &commandInBytes)
{
    const auto hash = BytesConverter::fromVectorOfUINT8toUINT32(commandInBytes, Frame::INITIAL_DATA_POSITION);

    auto command = make_unique<SetHashCommand>(hash);

    return move(command);
}
