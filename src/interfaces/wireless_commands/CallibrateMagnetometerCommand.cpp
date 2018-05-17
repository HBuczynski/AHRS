#include "CallibrateMagnetometerCommand.h"
#include "CommandVisitor.h"
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

CallibrateMagnetometerCommand::CallibrateMagnetometerCommand(const std::string &name)
    : Command(10,CommandType::CALIBRATE_MAGNETOMETER),
      newPlaneName_(name)
{}

CallibrateMagnetometerCommand::~CallibrateMagnetometerCommand()
{}

vector<uint8_t> CallibrateMagnetometerCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendStringToVectorOfUINT8(newPlaneName_, frame);

    return frame;
}

void CallibrateMagnetometerCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += newPlaneName_.size() + sizeof(END_STRING_IN_FRAME);

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
    newPlaneName_ = name;
}

const string &CallibrateMagnetometerCommand::getNewPlaneName() const
{
    return newPlaneName_;
}
