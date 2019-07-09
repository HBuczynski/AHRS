#include "FMResetCommunicationProcessCommand.h"
#include "FMCommandVisitor.h"

using namespace std;
using namespace communication;

FMResetCommunicationProcessCommand::FMResetCommunicationProcessCommand(config::UICommunicationMode mode)
        : FMCommand(10, FMCommandType::RESET_COMMUNICATION_PROCESS),
          mode_(mode)
{ }

FMResetCommunicationProcessCommand::~FMResetCommunicationProcessCommand()
{ }

vector<uint8_t> FMResetCommunicationProcessCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string FMResetCommunicationProcessCommand::getName()
{
    return string("FMResetCommunicationProcessCommand");
}

void FMResetCommunicationProcessCommand::accept(FMCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void FMResetCommunicationProcessCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(mode_);

    setDataSize(dataSize);
}

config::UICommunicationMode FMResetCommunicationProcessCommand::getMode() const
{
    return mode_;
}

void FMResetCommunicationProcessCommand::setMode(const config::UICommunicationMode &mode)
{
    mode_ = mode;
}
