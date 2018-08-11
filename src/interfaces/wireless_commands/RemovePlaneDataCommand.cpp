#include "RemovePlaneDataCommand.h"
#include "CommandVisitor.h"
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

RemovePlaneDataCommand::RemovePlaneDataCommand(const std::string &name)
    : Command(10, CommandType::REMOVE_PLANE_DATA),
      planeName_(name)
{}

RemovePlaneDataCommand::~RemovePlaneDataCommand()
{}

vector<uint8_t> RemovePlaneDataCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendStringToVectorOfUINT8(planeName_, frame);

    return frame;
}

void RemovePlaneDataCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += planeName_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}

string RemovePlaneDataCommand::getName()
{
    return string("RemovePlaneDataCommand");
}

void RemovePlaneDataCommand::setPlaneName(const std::string &name)
{
    planeName_=name;
}

const std::string &RemovePlaneDataCommand::getPlaneName() const
{
    return planeName_;
}

void RemovePlaneDataCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}