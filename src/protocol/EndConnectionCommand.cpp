#include "EndConnectionCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

EndConnectionCommand::EndConnectionCommand()
        : Command(10, CommandType::END_CONNECTION)
{}

EndConnectionCommand::~EndConnectionCommand()
{}

vector<uint8_t> EndConnectionCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string EndConnectionCommand::getName()
{
    return string("EndConnectionCommand");
}

void EndConnectionCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void EndConnectionCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_));
}
