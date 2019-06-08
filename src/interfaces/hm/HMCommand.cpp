#include "HMCommand.h"

using namespace std;
using namespace communication;

HMCommand::HMCommand(uint8_t dataSizeIn, HMCommandType notificationTypeIn)
        : Frame(FrameType::COMMAND, InterfaceType::HM, dataSizeIn),
          commandType_(notificationTypeIn)
{}

HMCommand::~HMCommand()
{}

const HMCommandType &HMCommand::getCommandType() const
{
    return commandType_;
}
