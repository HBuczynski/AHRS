#include "SetPlaneMagnetometerCommand.h"
#include "CommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

SetPlaneMagnetometerCommand::SetPlaneMagnetometerCommand(const std::string &name)
    : Command(10, CommandType::SET_PLANE_MAGNETOMETER_DATA),
      planeName_(name)
{}

SetPlaneMagnetometerCommand::~SetPlaneMagnetometerCommand()
{}

vector<uint8_t> SetPlaneMagnetometerCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendStringToVectorOfUINT8(planeName_, frame);

    return frame;
}

string SetPlaneMagnetometerCommand::getName()
{
    return string("SetPlaneMagnetometerCommand");
}

void SetPlaneMagnetometerCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void SetPlaneMagnetometerCommand::setPlaneName(const string &name)
{
    planeName_ = name;
}

const string &SetPlaneMagnetometerCommand::getPlaneName() const
{
    return planeName_;
}

void SetPlaneMagnetometerCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += planeName_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}
