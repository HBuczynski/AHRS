#include "HandshakeCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

HandshakeCommand::HandshakeCommand()
        : Command(10, CommandType::HANDSHAKE)
{}

HandshakeCommand::~HandshakeCommand()
{}

vector<uint8_t> HandshakeCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

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
    setDataSize(sizeof(commandType_));
}
