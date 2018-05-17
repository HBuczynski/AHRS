#include "InitConnectionBuilder.h"
#include "InitConnectionCommand.h"

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

    port = BytesConverter::fromVectorOfUINT8toUINT16(commandInBytes, INIT_PORT_POSITION_IN_FRAME);
    address = BytesConverter::fromVectorOfUINT8toString(commandInBytes, INIT_ADDRESS_POSITION_IN_FRAME);

    auto command = make_unique<InitConnectionCommand>(port, address);

    return move(command);
}


