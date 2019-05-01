#include "InitConnectionBuilder.h"
#include "InitConnectionCommand.h"

#include <iostream>
#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

InitConnectionBuilder::InitConnectionBuilder()
{}

InitConnectionBuilder::~InitConnectionBuilder()
{}

std::unique_ptr<Command> InitConnectionBuilder::create(const std::vector<uint8_t> &commandInBytes)
{
    uint16_t port;
    std::string address;
    uint16_t currentPoisition = Frame::INITIAL_DATA_POSITION;

    port = BytesConverter::fromVectorOfUINT8toUINT16(commandInBytes, currentPoisition);

    currentPoisition += sizeof(port);
    address = BytesConverter::fromVectorOfUINT8toString(commandInBytes, currentPoisition);

    auto command = make_unique<InitConnectionCommand>(port, address);

    return move(command);
}


