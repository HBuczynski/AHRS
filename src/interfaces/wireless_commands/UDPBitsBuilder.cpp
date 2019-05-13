#include "UDPBitsBuilder.h"
#include "UDPBitsCommand.h"

using namespace std;
using namespace communication;

UDPBitsBuilder::UDPBitsBuilder()
{}

UDPBitsBuilder::~UDPBitsBuilder()
{}

unique_ptr<Command> UDPBitsBuilder::create(const vector<uint8_t> &commandInBytes)
{
    auto command = make_unique<UDPBitsCommand>();

    return move(command);
}

