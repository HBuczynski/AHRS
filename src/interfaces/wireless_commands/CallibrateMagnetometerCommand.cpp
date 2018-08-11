#include "CallibrateMagnetometerCommand.h"
#include "CommandVisitor.h"
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

CallibrateMagnetometerCommand::CallibrateMagnetometerCommand(const std::string &name, PlaneStatus status)
    : Command(10,CommandType::CALIBRATE_MAGNETOMETER),
      planeName_(name),
      status_(status)
{}

CallibrateMagnetometerCommand::~CallibrateMagnetometerCommand()
{}

vector<uint8_t> CallibrateMagnetometerCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(status_));

    BytesConverter::appendStringToVectorOfUINT8(planeName_, frame);

    return frame;
}

void CallibrateMagnetometerCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += planeName_.size() + sizeof(END_STRING_IN_FRAME);
    dataSize += sizeof(status_);

    setDataSize(dataSize);
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
    planeName_ = name;
}

const string &CallibrateMagnetometerCommand::getPlaneName() const
{
    return planeName_;
}

void CallibrateMagnetometerCommand::setPlaneStatus(PlaneStatus status)
{
    status_ = status;
}

const PlaneStatus &CallibrateMagnetometerCommand::getPlaneStatus() const
{
    return status_;
}
