#include "GUIWindowCommand.h"
#include "GUICommandVisitor.h"

using namespace std;
using namespace communication;

GUIWindowCommand::GUIWindowCommand(PagesType windowType)
        : GUICommand(10, GUICommandType::CHANGE_WINDOW),
          windowType_(windowType)
{}

GUIWindowCommand::~GUIWindowCommand()
{}

vector<uint8_t> GUIWindowCommand::getFrameBytes()
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));
    frame.push_back(static_cast<uint8_t>(windowType_));

    return frame;
}

string GUIWindowCommand::getName()
{
    return string("GUIWindowCommand");
}

PagesType GUIWindowCommand::getWindowType() const
{
    return windowType_;
}

void GUIWindowCommand::setWindowType(PagesType windowType)
{
    windowType_ = windowType;
}

void GUIWindowCommand::accept(GUICommandVisitor &visitor)
{
    visitor.visit(*this);
}

void GUIWindowCommand::initializeDataSize()
{
    setDataSize(sizeof(commandType_) + sizeof(windowType_));
}