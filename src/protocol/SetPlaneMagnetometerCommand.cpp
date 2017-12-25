#include "SetPlaneMagnetometerCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

SetPlaneMagnetometerCommand::SetPlaneMagnetometerCommand()
    : Command(10, CommandType::SET_PLANE_MAGNETOMETER_DATA),
      planeName_("")
{}

SetPlaneMagnetometerCommand::~SetPlaneMagnetometerCommand()
{}

vector<uint8_t> SetPlaneMagnetometerCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    vector<uint8_t > name(planeName_.begin(), planeName_.end());
    frame.insert(frame.end(), name.begin(), name.end());

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
