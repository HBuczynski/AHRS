#include "HMInvalidConnectionCommand.h"
#include "HMCommandVisitor.h"

using namespace std;
using namespace communication;

HMInvalidConnectionCommand::HMInvalidConnectionCommand(uint8_t processNumber)
        : HMCommand(10, HMCommandType::INVALID_CONNECTION_COMM),
          processNumber_(processNumber)
{ }

HMInvalidConnectionCommand::~HMInvalidConnectionCommand()
{ }

vector<uint8_t> HMInvalidConnectionCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(processNumber_);

    return frame;
}

string HMInvalidConnectionCommand::getName()
{
    return string("HMInvalidConnectionCommand");
}

void HMInvalidConnectionCommand::accept(HMCommandVisitor &visitor)
{
    visitor.visit(*this);
}

void HMInvalidConnectionCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(processNumber_);

    setDataSize(dataSize);
}

uint8_t HMInvalidConnectionCommand::getProcessNumber() const
{
    return processNumber_;
}

void HMInvalidConnectionCommand::setProcessNumber(const uint8_t &processNumber)
{
    processNumber_ = processNumber;
}

