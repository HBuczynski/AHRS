#include "SetPlaneCommand.h"
#include "CommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

SetPlaneCommand::SetPlaneCommand(const std::string &name)
    : Command(10, CommandType::SET_PLANE_NAME),
      planeName_(name)
{}

SetPlaneCommand::~SetPlaneCommand()
{}

vector<uint8_t> SetPlaneCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendStringToVectorOfUINT8(planeName_, frame);

    return frame;
}

string SetPlaneCommand::getName()
{
    return string("SetPlaneCommand");
}

void SetPlaneCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void SetPlaneCommand::setPlaneName(const string &name)
{
    planeName_ = name;
}

const string &SetPlaneCommand::getPlaneName() const
{
    return planeName_;
}

void SetPlaneCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += planeName_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}
