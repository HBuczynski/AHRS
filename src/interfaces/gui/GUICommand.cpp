#include "GUICommand.h"

using namespace std;
using namespace communication;

GUICommand::GUICommand(uint8_t dataSizeIn, GUICommandType commandTypeIn)
        : Frame(FrameType::COMMAND, InterfaceType::GUI, dataSizeIn),
          commandType_(commandTypeIn)
{}

GUICommand::~GUICommand()
{}

const GUICommandType &GUICommand::getCommandType() const
{
    return commandType_;
}

