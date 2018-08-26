#include "ShutdownCommand.h"
#include "UICommandVisitor.h"

using namespace std;
using namespace communication;

ShutdownCommand::ShutdownCommand()
        : UICommand(10, UICommandType::SHUTDOWN)
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

void ShutdownCommand::accept(UICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void ShutdownCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
