#include "EndConnectionCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

EndConnectionCommand::EndConnectionCommand()
        : Command(10, CommandType::END_CONNECTION)
{
}

EndConnectionCommand::~EndConnectionCommand()
{
}

std::vector<uint8_t> EndConnectionCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();


    return frame;;
}

std::string EndConnectionCommand::getName()
{
    return string("EndConnectionCommand");
}

void EndConnectionCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}
