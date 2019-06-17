#include "EthHandshakeCommand.h"
#include "EthFeederCommandVisitor.h"

using namespace std;
using namespace communication;

EthHandshakeCommand::EthHandshakeCommand(config::FeederMode mode)
    : EthFeederCommand(10, EthCommandType::ETH_CHANGE_STATE),
      mode_(mode)
{}

EthHandshakeCommand::~EthHandshakeCommand()
{}

vector<uint8_t> EthHandshakeCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string EthHandshakeCommand::getName()
{
    return string("EthHandshakeCommand");
}

void EthHandshakeCommand::accept(EthFeederCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void EthHandshakeCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(mode_));
}

config::FeederMode EthHandshakeCommand::getMode() const
{
    return mode_;
}

void EthHandshakeCommand::setMode(const config::FeederMode &mode)
{
    mode_ = mode;
}
