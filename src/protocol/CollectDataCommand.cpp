#include "CollectDataCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;


CollectDataCommand::CollectDataCommand()
    : Command(10, CommandType::COLLECT_DATA)
{}

CollectDataCommand::~CollectDataCommand()
{}

vector<uint8_t> CollectDataCommand::getFrameBytes()
{
    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string CollectDataCommand::getName()
{
    return string("CollectDataCommand");
}

void CollectDataCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}
