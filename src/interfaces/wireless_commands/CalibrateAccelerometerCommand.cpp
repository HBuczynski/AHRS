#include "CalibrateAccelerometerCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

CalibrateAccelerometerCommand::CalibrateAccelerometerCommand(uint8_t axis, AccelAction action)
    : Command(10,CommandType::CALIBRATE_ACCELEROMETER),
      axis_(axis),
      action_(action)
{}

CalibrateAccelerometerCommand::~CalibrateAccelerometerCommand()
{}

vector<uint8_t > CalibrateAccelerometerCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(axis_);
    frame.push_back(static_cast<uint8_t>(action_));

    return frame;
}

string CalibrateAccelerometerCommand::getName()
{
    return string("CalibrateAccelerometerCommand");
}

void CalibrateAccelerometerCommand::accept(CommandVisitor& visitor)
{
    visitor.visit(*this);
}

uint8_t CalibrateAccelerometerCommand::getAxis() const noexcept
{
    return axis_;
}

void CalibrateAccelerometerCommand::setAxis(uint8_t axis) noexcept
{
    axis_ = axis;
}

void CalibrateAccelerometerCommand::setAction(AccelAction action) noexcept
{
    action_ = action;
}

AccelAction CalibrateAccelerometerCommand::getAction() const noexcept
{
    return action_;
}

void CalibrateAccelerometerCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(axis_);
    dataSize += sizeof(action_);

    setDataSize(dataSize);
}
