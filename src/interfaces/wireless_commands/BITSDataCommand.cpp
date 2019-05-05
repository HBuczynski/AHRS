#include "BITSDataCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

BITSDataCommand::BITSDataCommand()
    : Command(10,CommandType::BITS_DATA)
{}

BITSDataCommand::~BITSDataCommand()
{}

vector<uint8_t> BITSDataCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

void BITSDataCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    setDataSize(dataSize);
}

string BITSDataCommand::getName()
{
    return string("BITSDataCommand");
}

void BITSDataCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

