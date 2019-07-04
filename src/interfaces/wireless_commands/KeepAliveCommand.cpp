#include "KeepAliveCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

KeepAliveCommand::KeepAliveCommand()
        : Command(10, CommandType::KEEP_ALIVE)
{}

KeepAliveCommand::~KeepAliveCommand()
{}

vector<uint8_t> KeepAliveCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string KeepAliveCommand::getName()
{
    return string("KeepAliveCommand");
}

void KeepAliveCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void KeepAliveCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
