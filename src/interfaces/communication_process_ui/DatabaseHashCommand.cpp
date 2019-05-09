#include "DatabaseHashCommand.h"
#include "UICommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

DatabaseHashCommand::DatabaseHashCommand(uint32_t hash, const std::string& name)
    : UICommand(10, UICommandType::DATABASE_HASH),
      name_(name),
      hash_(hash)
{}

DatabaseHashCommand::~DatabaseHashCommand()
{}

vector<uint8_t> DatabaseHashCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    BytesConverter::appendUINT32toVectorOfUINT8(hash_, frame);
    BytesConverter::appendStringToVectorOfUINT8(name_, frame);

    return frame;
}

string DatabaseHashCommand::getName()
{
    return string("DatabaseHashCommand");
}

const std::string& DatabaseHashCommand::getDbName() const noexcept
{
    return name_;
}

void DatabaseHashCommand::setName(const std::string& name)
{
    name_ = name;
}

uint32_t DatabaseHashCommand::getHash() const noexcept
{
    return hash_;
}

void DatabaseHashCommand::setHash(uint32_t hash)
{
    hash_ = hash;
}

void DatabaseHashCommand::accept(UICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void DatabaseHashCommand::initializeDataSize()
{
    auto datasz = sizeof(hash_);
    datasz += sizeof(commandType_);
    datasz += name_.size() +1;

    setDataSize(datasz);
}
