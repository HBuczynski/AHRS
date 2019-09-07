#include "ShutdownCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

ShutdownCommand::ShutdownCommand()
        : Command(10, CommandType::SHUTDOWN_CMD)
{}

ShutdownCommand::~ShutdownCommand()
{}

vector<uint8_t> ShutdownCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string ShutdownCommand::getName()
{
    return string("ShutdownCommand");
}

void ShutdownCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void ShutdownCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}

