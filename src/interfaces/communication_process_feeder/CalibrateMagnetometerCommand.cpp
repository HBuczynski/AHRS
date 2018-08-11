#include "CalibrateMagnetometerCommand.h"

#include "FeederCommandVisitor.h"
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

CalibrateMagnetometerCommand::CalibrateMagnetometerCommand(const std::string &name)
    : FeederCommand(10, FeederCommandType::CALIBRATE_MAGNETOMETER),
      planeName_(name)
{ }

CalibrateMagnetometerCommand::~CalibrateMagnetometerCommand()
{ }

vector<uint8_t> CalibrateMagnetometerCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendStringToVectorOfUINT8(planeName_, frame);

    return frame;
}

void CalibrateMagnetometerCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += planeName_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}

string CalibrateMagnetometerCommand::getName()
{
    return string("CalibrateMagnetometerCommand");
}

void CalibrateMagnetometerCommand::setPlaneName(const std::string &name)
{
    planeName_ = name;
}

const string &CalibrateMagnetometerCommand::getPlaneName() const
{
    return planeName_;
}

void CalibrateMagnetometerCommand::accept(FeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}