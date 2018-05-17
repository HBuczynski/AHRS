#include "UIChangeModeCommand.h"
#include "UICommandVisitor.h"

using namespace std;
using namespace communication;

UIChangeModeCommand::UIChangeModeCommand(const CommunicationProcessMode &mode)
    : UICommand(10, UICommandType::CHANGE_STATE),
      mode_(mode)
{

}

UIChangeModeCommand::~UIChangeModeCommand()
{

}

vector<uint8_t> UIChangeModeCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(mode_));

    return frame;;
}

CommunicationProcessMode UIChangeModeCommand::getMode() const
{
    return mode_;
}

void UIChangeModeCommand::setMode(CommunicationProcessMode mode)
{
    mode_ = mode;
}

string UIChangeModeCommand::getName()
{
    return string("UIChangeModeCommand");
}

void UIChangeModeCommand::accept(UICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void UIChangeModeCommand::initializeDataSize()
{
    uint16_t dataSize = sizeof(commandType_);
    dataSize += sizeof(mode_);

    setDataSize(dataSize);
}
