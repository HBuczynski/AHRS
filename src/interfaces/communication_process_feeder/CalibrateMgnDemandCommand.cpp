#include "CalibrateMgnDemandCommand.h"

#include "FeederCommandVisitor.h"
#include <utility/BytesConverter.h>

#include <stdexcept>

using namespace std;
using namespace utility;
using namespace communication;

CalibrateMgnDemandCommand::CalibrateMgnDemandCommand(const std::string &name)
    : FeederCommand(10, FeederCommandType::CALIBRATE_MAGNETOMETER_DEMAND),
      planeName_(name)
{ }

CalibrateMgnDemandCommand::~CalibrateMgnDemandCommand()
{ }

vector<uint8_t> CalibrateMgnDemandCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    BytesConverter::appendStringToVectorOfUINT8(planeName_, frame);

    return frame;
}

void CalibrateMgnDemandCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += planeName_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}

string CalibrateMgnDemandCommand::getName()
{
    return string("CalibrateMgnDemandCommand");
}

void CalibrateMgnDemandCommand::setPlaneName(const std::string &name)
{
    planeName_ = name;
}

const string &CalibrateMgnDemandCommand::getPlaneName() const
{
    return planeName_;
}

void CalibrateMgnDemandCommand::accept(FeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}