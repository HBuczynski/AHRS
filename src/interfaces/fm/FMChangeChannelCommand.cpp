#include "FMChangeChannelCommand.h"
#include "FMCommandVisitor.h"

using namespace std;
using namespace communication;

FMChangeChannelCommand::FMChangeChannelCommand(uint8_t processNumber)
        : FMCommand(10, FMCommandType::CHANGE_CHANNEL),
          processNumber_(processNumber)
{ }

FMChangeChannelCommand::~FMChangeChannelCommand()
{ }

vector<uint8_t> FMChangeChannelCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(processNumber_));

    return frame;
}

string FMChangeChannelCommand::getName()
{
    return string("FMChangeChannelCommand");
}

void FMChangeChannelCommand::accept(FMCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void FMChangeChannelCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(processNumber_);

    setDataSize(dataSize);
}

uint8_t FMChangeChannelCommand::getProcessNumber() const
{
    return processNumber_;
}

void FMChangeChannelCommand::setProcessNumber(const uint8_t &processNumber)
{
    processNumber_ = processNumber;
}
