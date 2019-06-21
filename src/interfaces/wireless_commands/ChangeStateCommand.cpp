#include "ChangeStateCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

ChangeStateCommand::ChangeStateCommand(FeederStateCode feederStateCode)
    : Command(10, CommandType::CHANGE_FEEDER_STATE),
      feederStateCode_(feederStateCode)
{}

ChangeStateCommand::~ChangeStateCommand()
{}

vector<uint8_t> ChangeStateCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(feederStateCode_));

    return frame;
}

string ChangeStateCommand::getName()
{
    return string("ChangeStateCommand");
}

void ChangeStateCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void ChangeStateCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(feederStateCode_));
}

FeederStateCode ChangeStateCommand::getFeederStateCode() const
{
    return feederStateCode_;
}

void ChangeStateCommand::setFeederStateCode(const FeederStateCode &feederStateCode)
{
    feederStateCode_ = feederStateCode;
}

