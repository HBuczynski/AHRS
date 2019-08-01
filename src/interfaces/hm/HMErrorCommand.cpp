#include "HMErrorCommand.h"
#include "HMCommandVisitor.h"

#include <utility/BytesConverter.h>

using namespace std;
using namespace communication;

HMErrorCommand::HMErrorCommand(HMNodes node, HMErrorType error, config::UICommunicationMode mode, const string &systemState)
        : HMCommand(10, HMCommandType::COMMAND_ERROR),
          node_(node),
          error_(error),
          mode_(mode),
          systemState_(systemState)
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

    utility::BytesConverter::appendStringToVectorOfUINT8(systemState_, frame);

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
    dataSize += systemState_.size() + sizeof(END_STRING_IN_FRAME);

    setDataSize(dataSize);
}

std::string HMErrorCommand::getSystemState() const
{
    return systemState_;
}

void HMErrorCommand::setSystemState(const std::string &systemState)
{
    systemState_ = systemState;
}

config::UICommunicationMode HMErrorCommand::getMode() const
{
    return mode_;
}

void HMErrorCommand::setMode(const config::UICommunicationMode &mode)
{
    mode_ = mode;
}
