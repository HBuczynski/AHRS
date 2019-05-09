#include "SetHashCommand.h"
#include "CommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

SetHashCommand::SetHashCommand(uint32_t hash)
    : Command(10, CommandType::SET_HASH),
      hash_(hash)
{}

SetHashCommand::~SetHashCommand()
{}

vector<uint8_t> SetHashCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendUINT32toVectorOfUINT8(hash_, frame);

    return frame;
}

string SetHashCommand::getName()
{
    return string("SetHashCommand");
}

void SetHashCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void SetHashCommand::setHash(uint32_t hash)
{
    hash_ = hash;
}

uint32_t SetHashCommand::getHash() const noexcept
{
    return hash_;
}

void SetHashCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(hash_);

    setDataSize(dataSize);
}
