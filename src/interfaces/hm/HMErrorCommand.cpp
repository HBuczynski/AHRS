#include "HMErrorCommand.h"
#include "HMCommandVisitor.h"

using namespace std;
using namespace communication;

HMErrorCommand::HMErrorCommand(HMNodes node, HMErrorType error, config::UICommunicationMode mode)
        : HMCommand(10, HMCommandType::COMMAND_ERROR),
          node_(node),
          error_(error),
          mode_(mode)
{ }

HMErrorCommand::~HMErrorCommand()
{ }

vector<uint8_t> HMErrorCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(node_));
    frame.push_back(static_cast<uint8_t>(error_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;
}

string HMErrorCommand::getName()
{
    return string("HMErrorCommand");
}

void HMErrorCommand::accept(HMCommandVisitor &visitor)
{
    visitor.visit(*this);
}

HMNodes HMErrorCommand::getHMNode() const
{
    return node_;
}

void HMErrorCommand::setHMNode(HMNodes node)
{
    node_ = node;
}

HMErrorType HMErrorCommand::getHMError() const
{
    return error_;
}

void HMErrorCommand::setHMError(HMErrorType error)
{
    error_ = error;
}

void HMErrorCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(error_);
    dataSize += sizeof(node_);
    dataSize += sizeof(mode_);

    setDataSize(dataSize);
}

config::UICommunicationMode HMErrorCommand::getMode() const
{
    return mode_;
}

void HMErrorCommand::setMode(const config::UICommunicationMode &mode)
{
    mode_ = mode;
}
