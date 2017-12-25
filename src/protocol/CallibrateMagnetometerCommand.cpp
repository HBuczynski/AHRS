#include "CallibrateMagnetometerCommand.h"
#include "CommandVisitor.h"

#include <stdexcept>

using namespace std;
using namespace communication;

CallibrateMagnetometerCommand::CallibrateMagnetometerCommand()
    : Command(10,CommandType::CALIBRATE_MAGNETOMETER),
      newPlaneName_("")
{}

CallibrateMagnetometerCommand::~CallibrateMagnetometerCommand()
{}

vector<uint8_t> CallibrateMagnetometerCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    vector<uint8_t > name(newPlaneName_.begin(), newPlaneName_.end());
    frame.insert(frame.end(), name.begin(), name.end());

    return frame;
}

string CallibrateMagnetometerCommand::getName()
{
    return string("CallibrateMagnetometerCommand");
}

void CallibrateMagnetometerCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void CallibrateMagnetometerCommand::setNewPlaneName(const string &name)
{
    newPlaneName_ = name;
}

const string &CallibrateMagnetometerCommand::getNewPlaneName() const
{
    return newPlaneName_;
}
