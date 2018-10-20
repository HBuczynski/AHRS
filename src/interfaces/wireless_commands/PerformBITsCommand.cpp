#include "PerformBITsCommand.h"
#include "CommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

PerformBITsCommand::PerformBITsCommand()
        : Command(10, CommandType::PERFORM_BIT)
{}

PerformBITsCommand::~PerformBITsCommand()
{}

vector<uint8_t> PerformBITsCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string PerformBITsCommand::getName()
{
    return string("PerformBITsCommand");
}

void PerformBITsCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void PerformBITsCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    setDataSize(dataSize);;
}
