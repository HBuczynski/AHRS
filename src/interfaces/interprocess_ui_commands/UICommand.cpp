#include "UICommand.h"

using namespace std;
using namespace communication;

UICommand::UICommand(uint8_t dataSizeIn, UICommandType commandTypeIn)
    : Frame(FrameType::UI_COMMAND, dataSizeIn),
      commandType_(commandTypeIn)
{}

UICommand::~UICommand()
{}

const UICommandType &UICommand::getCommandType() const
{
    return commandType_;
}
