#include "CallibrateMagnetometerCommand.h"
#include "CommandVisitor.h"
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

CallibrateMagnetometerCommand::CallibrateMagnetometerCommand(Action status)
    : Command(10,CommandType::CALIBRATE_MAGNETOMETER),
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

    return frame;
}

void CallibrateMagnetometerCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
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

void CallibrateMagnetometerCommand::setMagAction(Action status)
{
    status_ = status;
}

const Action &CallibrateMagnetometerCommand::getMagAction() const
{
    return status_;
}
