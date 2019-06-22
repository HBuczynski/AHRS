#include "HandshakeCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

HandshakeCommand::HandshakeCommand(config::FeederMode mode)
        : Command(10, CommandType::HANDSHAKE),
          mode_(mode)
{}

HandshakeCommand::~HandshakeCommand()
{}

vector<uint8_t> HandshakeCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string HandshakeCommand::getName()
{
    return string("HandshakeCommand");
}

void HandshakeCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void HandshakeCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(mode_));
}

config::FeederMode HandshakeCommand::getMode() const
{
    return mode_;
}

void HandshakeCommand::setMode(const config::FeederMode &mode)
{
    mode_ = mode;
}
