#include "RestartCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

RestartCommand::RestartCommand()
        : Command(10, CommandType::RESTART_CMD)
{}

RestartCommand::~RestartCommand()
{}

vector<uint8_t> RestartCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string RestartCommand::getName()
{
    return string("RestartCommand");
}

void RestartCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void RestartCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
