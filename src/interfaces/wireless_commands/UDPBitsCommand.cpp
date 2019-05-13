#include "UDPBitsCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

UDPBitsCommand::UDPBitsCommand()
    : Command(10,CommandType::UDP_BITS)
{}

UDPBitsCommand::~UDPBitsCommand()
{}

vector<uint8_t> UDPBitsCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

void UDPBitsCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    setDataSize(dataSize);
}

string UDPBitsCommand::getName()
{
    return string("UDPBitsCommand");
}

void UDPBitsCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}
