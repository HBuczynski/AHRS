#include "ChangeFeederModeCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

ChangeFeederModeCommand::ChangeFeederModeCommand(config::FeederMode mode)
        : Command(10, CommandType::CHANGE_FEEDER_MODE),
          mode_(mode)
{}

ChangeFeederModeCommand::~ChangeFeederModeCommand()
{}

vector<uint8_t> ChangeFeederModeCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string ChangeFeederModeCommand::getName()
{
    return string("ChangeFeederModeCommand");
}

void ChangeFeederModeCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void ChangeFeederModeCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(mode_));
}

config::FeederMode ChangeFeederModeCommand::getMode() const
{
    return mode_;
}

void ChangeFeederModeCommand::setMode(const config::FeederMode &mode)
{
    mode_ = mode;
}
