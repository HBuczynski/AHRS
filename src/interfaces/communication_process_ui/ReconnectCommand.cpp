#include "ReconnectCommand.h"
#include "UICommandVisitor.h"

using namespace std;
using namespace communication;

ReconnectCommand::ReconnectCommand()
    : UICommand(10, UICommandType::RECONNECT)
{}

ReconnectCommand::~ReconnectCommand()
{}

vector<uint8_t> ReconnectCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string ReconnectCommand::getName()
{
    return string("ReconnectCommand");
}

void ReconnectCommand::accept(UICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void ReconnectCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
