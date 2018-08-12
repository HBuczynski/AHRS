#include "CurrentStateCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

CurrentStateCommand::CurrentStateCommand()
    : Command(10, CommandType::CURRENT_STATE)
{}

CurrentStateCommand::~CurrentStateCommand()
{}

vector<uint8_t> CurrentStateCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string CurrentStateCommand::getName()
{
    return string("CurrentStateCommand");
}

void CurrentStateCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void CurrentStateCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
