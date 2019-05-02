#include "SetPlaneBuilder.h"
#include "SetPlaneCommand.h"

#include <utility/BytesConverter.h>
#include <iostream>

using namespace std;
using namespace utility;
using namespace communication;

SetPlaneBuilder::SetPlaneBuilder()
{}

SetPlaneBuilder::~SetPlaneBuilder()
{}

unique_ptr<Command> SetPlaneBuilder::create(const vector<uint8_t> &commandInBytes)
{
    string planeName;

    planeName = BytesConverter::fromVectorOfUINT8toString(commandInBytes, Frame::INITIAL_DATA_POSITION);

    auto command = make_unique<SetPlaneCommand>(planeName);

    return move(command);
}


