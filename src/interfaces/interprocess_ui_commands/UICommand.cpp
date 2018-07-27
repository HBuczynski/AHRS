#include "UICommand.h"

using namespace std;
using namespace communication;

UICommand::UICommand(uint8_t dataSizeIn, UICommandType commandTypeIn)
    : Frame(FrameType::COMMAND, InterfaceType::GUI, dataSizeIn),
      commandType_(commandTypeIn)
{}

UICommand::~UICommand()
{}

const UICommandType &UICommand::getCommandType() const
{
    return commandType_;
}
